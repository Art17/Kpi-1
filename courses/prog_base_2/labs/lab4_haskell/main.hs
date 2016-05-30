module Main where

import Network
import Control.Concurrent
import System.IO

import Web

main = withSocketsDo $ do
    socket <- listenOn $ PortNumber 5000
    loop socket

loop socket = do
    (handle, hostname, port) <- accept socket
    serverReply handle
    loop socket