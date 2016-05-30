module Validator where

import Data.Maybe
import Data.Char
import Text.Read
import Data.List.Split

isValidName :: String -> Bool
isValidName "" = False
isValidName l = isValidName' l

isValidName' :: String -> Bool
isValidName' "" = True
isValidName' (x:[]) = not (isDigit x)
isValidName' (x:l) = not (isDigit x) && isValidName' l

isValidDate :: String -> Bool
isValidDate str = if (length str == 10)
                    then do
                        let list = splitOn "-" str
                        if (length list == 3)
                            then do
                                let my = readMaybe (list !! 0) :: Maybe Int
                                let mm = readMaybe (list !! 1) :: Maybe Int
                                let md = readMaybe (list !! 2) :: Maybe Int
                                if (isJust my && isJust mm && isJust md)
                                    then if (fromJust mm <= 12 && fromJust md <= 31)
                                            then True
                                            else False
                                    else False
                            else False
                    else False
