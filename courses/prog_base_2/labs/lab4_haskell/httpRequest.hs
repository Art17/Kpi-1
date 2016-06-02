module HttpRequest where

import Network
import Control.Concurrent
import System.IO
import Control.Monad

import Data.List.Split

import qualified Data.ByteString as B
import qualified Data.ByteString.Char8 as C
import Data.ByteString.UTF8 (toString, fromString)

type Text = [Char]

data Method = GET | POST | DELETE | OPTIONS | HEAD | PUT | CONNECT | TRACE | UNKNOWN deriving (Show, Eq)
data HttpRequest = HttpRequest { method :: Method, uri :: [String], form :: [String] };
data HttpResponse = HttpResponse { code :: Int, reason :: String, contentType :: String, contentLength :: Int, buffer :: String }

instance Show HttpResponse where
    show r = "HTTP/1.1 " ++ (show $ code r) ++ " " ++ (reason r) ++ "\r\n" ++
             "Content-Type: " ++ (contentType r) ++ "\r\n" ++
             "Content-Length: " ++ (show $ contentLength r) ++ "\r\n\r\n" ++
             (buffer r)
             

methodFromString :: String -> Method
methodFromString m = case m of
                          "GET" -> GET
                          "POST" -> POST
                          "DELETE" -> DELETE
                          "OPTIONS" -> OPTIONS
                          "HEAD" -> HEAD
                          "PUT" -> PUT
                          "CONNECT" -> CONNECT
                          "TRACE" -> TRACE
                          _         -> UNKNOWN
parseBuffer :: B.ByteString -> HttpRequest
parseBuffer buffer = HttpRequest {
                                   method = parseMethod buffer,
                                   uri = parseUri buffer,
                                   form = parseBody buffer}

parseMethod :: B.ByteString -> Method
parseMethod str = methodFromString ( toString $ fst $ B.breakSubstring (C.pack " ") str )

parseUri :: B.ByteString -> [String]
parseUri message = map toString $ C.split '/' uriText
    where
        (_, uriStart) = B.breakSubstring (C.pack "/") message
        (uriText, _)  = B.breakSubstring (C.pack " ") (C.drop 1 uriStart)

parseBody :: B.ByteString -> [String]
parseBody str = (splitOn "&" (toString $ C.drop 4 preBody) )
    where
        preBody = (snd $ B.breakSubstring (C.pack "\r\n\r\n") str)