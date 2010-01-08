ADD_EXECUTABLE( factorial.exe
                main
                primesieve
                primeswing
                parallelprimeswing
                scopetimeprinter
                timer )

TARGET_LINK_LIBRARIES( factorial.exe
                       gmp
                       boost_thread-mt )

