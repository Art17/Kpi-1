module Utility where

removeByIndex :: [a] -> Int -> [a]
removeByIndex list index = removeByIndex' list index 0

removeByIndex' :: [a] -> Int -> Int -> [a]
removeByIndex' [] _ _ = []
removeByIndex' (h:t) index i
    | i == index = removeByIndex' t index (i+1)
    | otherwise  = [h] ++ (removeByIndex' t index (i+1))