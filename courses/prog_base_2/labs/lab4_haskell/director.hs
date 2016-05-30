{-# LANGUAGE Arrows #-}
module Director where

data Director = Director {
    name :: String,
    surname :: String,
    birthdate :: String,
    budget :: Double,
    years :: Int
    }
    
instance Show Director where
    show dir = (name dir) ++ " " ++ (surname dir) ++ " was born on " ++ (birthdate dir) ++ ". " ++
                "Has " ++ (show $ budget dir) ++ " budget " ++ "and " ++ (show $ years dir) ++ " years experience" 

showAsXml :: Director -> String
showAsXml dir = 
                "<director>\n" ++
                "  <name>"++ (name dir) ++"</name>\n" ++
                "  <surname>"++ (surname dir) ++"</surname>\n" ++
                "  <birthdate>"++ (birthdate dir) ++"</birthdate>\n" ++
                "  <budget>"++ (show $ budget dir) ++"</budget>\n" ++
                "  <years>"++ (show $ years dir) ++"</years>\n" ++
                "</director>\n"
                