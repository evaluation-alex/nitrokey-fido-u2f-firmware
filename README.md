Nitrokey FIDO U2F
===================

Nitrokey FIDO U2F is based on U2F Zero, an open source, open hardware U2F token for 2 factor authentication.  It is implemented securely.  It works with Google accounts, Github, Duo, and anything else supporting U2F.  The latest version uses key derivation and has no limit on registrations.

Hardware files are provided [here](https://github.com/Nitrokey/nitrokey-fido-u2f-hardware). Nitrokey's device differs in using a touch button instead of a regular one, as well as using smaller PCB.


Build (Ubuntu 18.04)
-----

1. Download Simplicity Studio 3 [link](https://www.silabs.com/products/development-tools/software/simplicity-studio-version3) (v4 will make bigger binary, which will not fit). 
2. Unpack it and run `./setup.sh` script.
3. Rename internal wine installation: `cd SimplicityStudio_v3/developer/utilities/third-party && mv wine{,_}`.
3. Install `wine-stable` package: `sudo apt install wine-stable`.
4. Run Studio.
5. Select and download proper dev kit (will be autodetected if debugger and device are connected).
6. Register KEIL compiler.
7. Build the source.

Usage (Ubuntu 18.04)
-------
Udev rules might be required to use the device without administrator privileges. Please run `./install_rules.sh` script, which will copy rules file to system directory on Ubuntu. For other OSes - please check the proper path and issue the copying manually.



Security Overview
-----------------

The security level is about the same as a modern car key.  Any secret information cannot be read or duplicated.  A true random number generator is used to create unpredictable keys.  

However, side channel leakage is an unsolved problem in industry and academia.  So for well equipped adversaries that can make targetted attacks and get physical access, secret information leakage is possible.  Any other hardware token that claims it's "impenetrable" or otherwise totally secure is *still* vulnerable to physical side channels and it's important to acknowledge.  However, most people don't worry about targeted attacks from well equipped adversaries.

For more information about U2F Zero's secure implementation and the problem of side channels, check out [the wiki](https://github.com/conorpp/u2f-zero/wiki/Security-Overview).


License
-------

Project maintains the original [Simplified BSD License](LICENSE.txt).
