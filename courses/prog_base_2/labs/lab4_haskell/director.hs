{-# LANGUAGE Arrows #-}
module Director where

import Text.XML.HXT.Core

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

createDirectorXmlNode :: ArrowXml a => Director -> a XmlTree XmlTree
createDirectorXmlNode dir =
    mkelem "director" []
    [   mkelem "name" [] [txt $ name dir],
        mkelem "surname" [] [txt $ surname dir],
        mkelem "birthdate" [] [txt $ birthdate dir],
        mkelem "budget" [] [txt $ show $ budget dir],
        mkelem "years" [] [txt $ show $ years dir]     ]
    
createDirectorXmlNodes' :: ArrowXml a => [Director] -> [a XmlTree XmlTree]
createDirectorXmlNodes' [] = []
createDirectorXmlNodes' (h:t) = ( [createDirectorXmlNode h] ++ createDirectorXmlNodes' t )

createDirectorXmlNodes :: ArrowXml a => [Director] -> a XmlTree XmlTree
createDirectorXmlNodes dirs =
    mkelem "directors" [] (createDirectorXmlNodes' dirs)
                