import Control.Monad
main = do
    n <- readLn
    replicateM_ n (putStrLn "Hello World")
