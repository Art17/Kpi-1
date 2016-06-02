{-# LANGUAGE Arrows #-}
module Web where

import Network
import Control.Concurrent
import System.IO
import Control.Monad
import Data.List

import qualified Data.ByteString as B
import Data.List.Split

import Data.Maybe

import Text.XML.HXT.Core
import Control.Arrow
import Control.Monad

import HttpRequest
import Director
import Validator
import Utility

import Text.Read

type Directors = [Director]

atTag tag = deep (isElem >>> hasName tag)
text = getChildren >>> getText

getDirector = atTag "director" >>>
  proc x -> do
    name <- text <<<      atTag "name" -< x
    surname <- text <<<   atTag "surname" -< x
    birthdate <- text <<< atTag "birthdate" -< x
    budget <- text <<<    atTag "budget" -< x
    years <- text <<<     atTag "years" -< x
    returnA -< Director { name = name, surname = surname, birthdate = birthdate, budget = (read budget :: Double), years = (read years :: Int) }

serverReply :: Handle -> IO ()
serverReply handle = do
    requestBuffer <- B.hGetSome handle 4096
    let httpRequest = parseBuffer requestBuffer

    directors <- runX (readDocument [withValidate no] "data/directors.xml" >>> getDirector)
    case (method httpRequest) of
        GET -> case (uri httpRequest) of
                    []                           -> serverHomepage handle
                    ["about", "author"]          -> serverAboutAuthor handle
                    ["directors"]                -> serverDirectorsMenu handle directors
                    ["directors", numBuf]        -> do
                                                      let id = (readMaybe numBuf) :: (Maybe Int)
                                                      case id of
                                                        Just n -> if (n >= 0 && n < length directors)
                                                                    then serverDirectorInfo handle (directors !! n) n
                                                                    else serverMessagePage handle 404 "NOT FOUND" "text" "Invalid index"
                                                        Nothing -> serverMessagePage handle 404 "NOT FOUND" "text" "Invalid index"
                    ["new-director"]             -> serverNewDirector handle
                    ["api", "directors"]         -> serverApiAllDirectors handle directors
                    ["api", "directors", numBuf] -> do
                                                      let id = (readMaybe numBuf) :: (Maybe Int)
                                                      case id of
                                                        Just n -> if (n >= 0 && n < length directors)
                                                                    then do
                                                                        strXml <- runX (root [] [createDirectorXmlNode $ directors !! n] >>> writeDocumentToString [withIndent yes])
                                                                        serverPlainMessagePage handle 200 "OK" "text/xml" (unlines strXml)
                                                                    else serverMessagePage handle 404 "NOT FOUND" "text" "Invalid index"
                                                        Nothing -> serverMessagePage handle 404 "NOT FOUND" "text" "Invalid index"
                    _                            -> serverMessagePage handle 404 "NOT FOUND" "text" "Invalid uri"
        OPTIONS -> serverOptions handle
        DELETE  -> case (uri httpRequest) of
                        ["directors", numBuf]    -> do
                                                      let id = read numBuf :: Int
                                                      let newDirs = removeByIndex directors id
                                                      runX (root [] [createDirectorXmlNodes newDirs] >>> writeDocument [withIndent yes] "data/directors.xml")
                                                      return ()
                                                      
                        ["api", "directors", numBuf] -> do
                                                          let id = (readMaybe numBuf) :: (Maybe Int)
                                                          case id of
                                                            Just n -> if (n >= 0 && n < length directors)
                                                                        then do
                                                                          let newDirs = removeByIndex directors n
                                                                          runX (root [] [createDirectorXmlNodes newDirs] >>> writeDocument [withIndent yes] "data/directors.xml")
                                                                          serverPlainMessagePage handle 200 "OK" "text" "Director deleted successfully"
                                                                        else
                                                                            serverPlainMessagePage handle 404 "NOT FOUND" "text" "Invalid index"
                                                            Nothing -> serverPlainMessagePage handle 404 "NOT FOUND" "text" "Invalid index"
                        _                        -> serverMessagePage handle 404 "NOT FOUND" "text" "Invalid uri"
        POST ->
              if ( (uri httpRequest) == ["api", "directors"] || (uri httpRequest) == ["directors"] )
                then do
                  let name = (getFormValue (form httpRequest) "name")
                  let surname = (getFormValue (form httpRequest) "surname")
                  let birthdate = (getFormValue (form httpRequest) "birthdate")
                  let budget=(readMaybe (getFormValue (form httpRequest) "budget") :: Maybe Double)
                  let years=(readMaybe (getFormValue (form httpRequest) "years") :: Maybe Int)
                  
                  if ( isJust years && isJust budget && isValidName name && isValidName surname && isValidDate birthdate &&
                        fromJust years > 0 && fromJust budget > 0)
                    then do
                      let newDir = Director { name=name,
                          surname=surname,
                          birthdate=birthdate,
                          budget= fromJust budget,
                          years= fromJust years}
                      runX (root [] [createDirectorXmlNodes $ [newDir] ++ directors] >>> writeDocument [withIndent yes] "data/directors.xml")
                      serverMessagePage handle 200 "OK" "text" "Director added successfully"
                    else
                      serverMessagePage handle 200 "OK" "text" "Invalid data passed"
                else
                    serverMessagePage handle 404 "NOT FOUND" "text" "Not found"
        UNKNOWN -> return ()
        _ ->  serverMessagePage handle 404 "NOT FOUND" "text" "Not found"

getFormValue :: [String] -> String -> String
getFormValue [] _ = ""
getFormValue (x:r) key   | ((head kvList)==key) = last kvList
                         | otherwise = getFormValue r key
                         where kvList = (splitOn "=" x)

serverApiAllDirectors :: Handle -> Directors -> IO ()
serverApiAllDirectors handle dirs = do
    strXml <- runX (root [] [createDirectorXmlNodes dirs] >>> writeDocumentToString [withIndent yes])
    serverPlainMessagePage handle 200 "OK" "text/xml" (unlines strXml)
        
serverOptions :: Handle -> IO ()
serverOptions handle = do
    let buffer = "HTTP/1.1 200 OK\n" ++ 
                 "Access-Control-Allow-Origin: *\n" ++ 
                 "Access-Control-Allow-Methods: DELETE\n" ++ 
                 "\n"
    let response = HttpResponse {code = 200,
                                 reason = "OK",
                                 contentType = "text",
                                 contentLength = (length buffer),
                                 buffer = buffer}
    hPutStr handle (show response)
    hClose handle

        
serverDirectorInfo :: Handle -> Director -> Int -> IO ()
serverDirectorInfo handle dir ind = do
    let buffer =
                 "<body>" ++
                 "<font size=\"5\">" ++ (show dir) ++ "</font><br><br>" ++
                 "<font size=\"5\"><a href=\"#\" onclick=\"doDelete()\">Delete director</a></font>" ++
                 "<script>" ++ 
                     "function doDelete() {" ++
                         "var xhttp = new XMLHttpRequest();" ++
                         "xhttp.open(\"DELETE\", \"http://localhost:5000/directors/"++ show (ind) ++"\", true);" ++
                         "xhttp.send();" ++
                     "}" ++
                 "</script>" ++
                 "</body>"
                 
    let response = HttpResponse {code = 200,
                                 reason = "OK",
                                 contentType = "text",
                                 contentLength = (length buffer),
                                 buffer = buffer}
    hPutStr handle (show response)
    hClose handle

        
serverDirectorsMenu :: Handle -> Directors -> IO ()
serverDirectorsMenu handle directors = do
    let directorsRefs = createDirectorsRefs directors
    let directorsMenuPage = "<h2>Direcors menu</h2>" ++
                            "<font size=\"5\">" ++
                            directorsRefs ++
                            "</font>" ++
                            "<br>" ++
                            "<font size=\"5\">" ++
                            "<a href=\"/new-director\">" ++
                            "Create new director" ++
                            "</a>" ++
                            "</font>"
    let response = HttpResponse {code = 200,
                                 reason = "OK",
                                 contentType = "text",
                                 contentLength = (length directorsMenuPage),
                                 buffer = directorsMenuPage}
    hPutStr handle (show response)
    hClose handle

serverNewDirector :: Handle -> IO ()
serverNewDirector handle = do
    let newDirectorPage =
                          "<form action=\"/directors\" method=\"POST\">" ++
                          "<fieldset>" ++
                          "<legend>Director information:</legend>" ++
                          "Name:<br>" ++
                          "<input type=\"text\" name=\"name\" value=\"\"><br>" ++
                          "Surname:<br>" ++
                          "<input type=\"text\" name=\"surname\" value=\"\"><br>" ++
                          "Birthdate:<br>" ++
                          "<input type=\"text\" name=\"birthdate\" value=\"\"><br>" ++
                          "Budget:<br>" ++
                          "<input type=\"text\" name=\"budget\" value=\"\"><br>" ++
                          "Years:<br>" ++
                          "<input type=\"text\" name=\"years\" value=\"\"><br><br>" ++
                          "<input type=\"submit\" value=\"Submit\">" ++
                          "</fieldset>" ++
                          "</form>"
    let response = HttpResponse {code = 200,
                                 reason = "OK",
                                 contentType = "text",
                                 contentLength = (length newDirectorPage),
                                 buffer = newDirectorPage}
    hPutStr handle (show response)
    hClose handle

    
serverHomepage :: Handle -> IO ()
serverHomepage handle = do
    let homepage = "<h2>Welcome to directors club</h2>" ++
                   "<br>" ++
                   "<font size=\"5\">" ++ 
                   "<a href=\"/directors\">1. Go to directors</a>" ++
                   "<br>" ++
                   "<a href=\"/about/author\">2. About author</a>" ++
                   "</font>" ++
                   "<br>" ++
                   "<br>" ++
                   "<font size=\"4\">Created on HASKELL</font>"
    let response = HttpResponse {code = 200,
                                 reason = "OK",
                                 contentType = "text",
                                 contentLength = (length homepage),
                                 buffer = homepage}
    hPutStr handle (show response)
    hClose handle

    
serverAboutAuthor :: Handle -> IO ()
serverAboutAuthor handle = do
    let aboutAuthorData = "<font size=\"5\">This server was created by Saprykin Artem on Haskell!</font>"
    let response = HttpResponse {code = 200,
                                 reason = "OK",
                                 contentType = "text",
                                 contentLength = (length aboutAuthorData),
                                 buffer = aboutAuthorData}
    hPutStr handle (show response)
    hClose handle

    
serverMessagePage :: Handle -> Int -> String -> String -> String -> IO ()
serverMessagePage handle code reason contentType message = do
    let buffer = "<font size = \"5\">" ++ message ++ "</font>"
    let response = HttpResponse {code = code,
                                 reason = reason,
                                 contentType = contentType,
                                 contentLength = (length buffer),
                                 buffer = buffer}
    hPutStr handle (show response)
    hClose handle
 
serverPlainMessagePage :: Handle -> Int -> String -> String -> String -> IO ()
serverPlainMessagePage handle code reason contentType message = do
    let response = HttpResponse {code = code,
                                 reason = reason,
                                 contentType = contentType,
                                 contentLength = (length message),
                                 buffer = message}
    hPutStr handle (show response)
    hClose handle

createDirectorsRefs :: Directors -> String
createDirectorsRefs dirs = createDirectorsRefs' dirs 0

createDirectorsRefs' :: Directors -> Int -> String
createDirectorsRefs' dirs ind
                              | ind >= (length dirs) = ""
                              | otherwise            = "<a href = \"/directors/" ++ (show ind) ++ "\">" ++ show (ind+1) ++ ". " ++
                                                       (name $ dirs !! ind) ++ " " ++ (surname $ dirs !! ind) ++
                                                       "</a><br>" ++ (createDirectorsRefs' dirs (ind+1))
                                                      
takedrop :: Int -> Int -> [a] -> [a]
takedrop _ _ [] = []
takedrop n m l  = take n l ++ takedrop n m (drop (n + m) l)
