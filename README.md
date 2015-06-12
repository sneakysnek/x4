#  Welcome to X4...
**X4 is built from the ground up with a brand new core design that is modular based and includes many changes that should be a high point in these fantastic services.**


## New features include:
   - A completely new engine for faster and smarter handling of events.
   - A modular design to handle plug and play module support.
   - Multiple password hashing formats.
   - Multiple IRCd protocol support.
   - Database interacting for hardfile, LDAP, MySQL, etc.
   - Built in statistics system.
   - Integration for websites/forums for universal logins.
   - Dynamic command/help listings that show what you have access to.
   - Out of date notifications.


### TESTING AND DEVELOPMENT:
In early stages of testing and development, we will be testing X4 on the following operating Linux distributions:

  - CentOS 6
  - Ubuntu 14
  - Ubuntu 15


### COMPATIBILITY:
This version of X services will support P10 natively with community support available for TS5, TS6, and any other protocols contributed.


### API:
One of X4's biggest features is it's entirely API based handling for pretty much every event that occurs. Everything from handling user authentication will be sent via API to the core and modules to ensure account security. The API is the controller interface that all data is passed through and parsed before returning an error or result. **Sacrificing security isn't an option.**


### MODULES:
The key element of X4 from it's predecessor is it's support for modules both designed by evilnet and third party modules. Modules will be available on the X4 website for download and testing, as well as reviews, comments, and feedback.

A possible plan of attack is an SSH based module control system that will allow a user to search modules on the site, as well as download and install them as needed.


### PROTOCOL:
X4's design will allow for additional IRC protocol's to be used so you can always use it with your favorite IRCd. Initially, the only protocol we will be designing will be P10 for use with Nefarious 2, but others may be created in time, if not from us, then from the community.


### DATA STORAGE AND USAGE:
One of the key changes in X4 from X3 is it's large scale usage of the data obtained and how it can be stored. With X3 you were limited to LDAP and hardfile unless you spent hours writing your own data handler or hacked together some changes to take care of what you needed.

The plan is to have a more universal system with a wider range of support which will include (but not limited to):
 
   - LDAP
   - SQL (MySQL, PostgreSQL, SQLite, etc.)
   - Hardfile (traditional X3 style)
   - XML

   
All the data is passed through the API for incoming and outgoing traffic control to prevent security issues.


### STATISTICS:
This will be designed modular and configured upon setup whether you wish to run it or not. The statistics will save to a database of your choosing and continue to collect during normal running operations.

The stats collected will only be basic and will not include chat logs or actual events, just totals on a network, channel and user level. Statistics also will not monitor anywhere X4 isn't (such as PM's).

Statistics will be usable for your website/forum or within IRC as a print out based on the specified subject.


### HASHING ALGORITHM:
Unlike X3, we will have multiple formats for password hashings to give the end user a choice. The only choice we don't condone is plain text.

Some of the hashing formats available in X4 will include:
 
   - SHA512          
   - SHA256
   - SHA1
   - MD5


For X3 users, migrating will be easy. Upon setting up X4's configuration file, make sure you include that you are moving from X3 so passwords will be converted upon user login to the new algorithm.

X3's legacy hashing algorithm will be obsolete with the release of X4. You will **NOT** be able to convert backwards in the future. Upon login, users will have their passwords converted to one of the above algorithm's including a new type variable included in the salted password string.

X4 is licensed under GPL, see LICENSE.
