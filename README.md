S.M.F.E. Simple M.A.M.E. Frontend **S.M.F.E.  
Simple M.A.M.E. Frontend**

![a palm tree](../images/palmtree.gif "a palm tree")

Quote from pugsy's site: _"My current MAME frontend of choice, fully featured and requires no installation at all, just run the exe (so it even works with MAME straight off a dvdr with very little work). And it hasn't crashed once!"_ :-)

|     |     |
| --- | --- |
| **Download** |     |
| **Binary:** | • [smfe.exe](smfe.exe) \[2.8MB\] or [smfe12.rar](smfe12.rar) \[0.8Mb\] Version 0.12, (26/Jun/2005), tested with **MAME 0.97b**  <br>• you may optionally get [smfe_data.rar](smfe_data.rar) \[0.9MB\] if you have trouble creating your own. |
| **Info:** | • No installation needed, just run smfe.exe. You must also have mame.exe (or mamepp.exe).  <br>• Check "Help->Getting Started" on how to read game data et.c  <br>• You can sort the table by multiple columns with shift+clicking on their headers  <br>• smfe creates smfe_data.dat which contains all displayed table information, and smfe.ini which contains saved options  <br>• **You must remove the old .dat file when you change smfe versions**  <br>• If mame.exe can find MAMEINFO.dat, it will use it and smfe will display recommended games. |
| **Sources:** | You can get the sources (v0.9) [smfe09-src.rar](smfe09-src.rar). To compile it you will need Borland C++ Builder, Russian Extensions (RX), ADVStringGrid. |
| **Misc:** | A shell script (for unix) [getrom](getrom) to download a rom from www.mame.dk. Usage: "getrom &lt;romname&gt;". If you don't have the "[socket](http://home.snafu.de/jn/socket/)" program, use [netcat.](http://www.atstake.com/research/tools/index.html#network_utilities)**Update:** www.mame.dk has shut down. |
| **Old Binaries** | • [smfe11.rar](smfe11.rar) \[818Kb\] for MAME 0.83  <br>• [smfe09.rar](smfe09.rar) \[818Kb\] Version 0.9, (30/Sep/2004), tested with **MAME 0.83**  <br>• [smfe07.zip](smfe07.zip) version 0.7 (2/Sep/2002), for **MAME 0.61** |

|     |
| --- |
| **Features** |
| * Simple means simple to use (hopefully)!<br>* Configurable image locations<br>* Supports PNG, JPG, TIF, GIF, BMP & .ICO formats<br>* Configurable mame.exe location<br>* **Supports network drives & UNC paths (\\\hostname\\sharename\\directory)**<br>* Can configure various MAME options for video, audio and input options and directory locations.<br>* Also supports using the mame.ini configuration file<br><br>* Reads supported MAME games from the MAME executable<br>* Checks for rom existence in the system (fast)<br>* Checks for rom validity (not so fast)<br>* Displays recommended games<br>* Supports nplayers.ini parsing (# of players each game supports)<br>* Supports HISTORY.DAT parsing (various game info)<br>* Saves Table data into file to avoid rerunning time-consuming operations<br>* Can kill the mame executable and change back screen resolution in case MAME hangs up. **(Ctrl+K)**<br>* Tested only with Windows 2000<br>    <br>* Table columns include: ROM name, description, Year, Manufacturer, Clone Info, Played times, Rom Size, Emulated CPU, Game type (raster/vector), Resolution.<br>* Supports **multi-column sort** (shift+click)<br>* For each game there is additional info displayed which includes recommended games and other game info.<br>* Can export all data in .XLS, .HTML and .TXT formats<br>    <br>* Options&paths are saved in smfe.ini, and game info/availability in smfe_data.dat at the same directory as the smfe.exe. It does **not** use the registry.<br>* **Can run from read-only (CDROM/DVDROM) media** just generate the .dat file once and place along it with the .exe and .ini |
| **TODO** |
| * Record audio in .mp3 format (HELP!)<br>* Display the main form rotated. This can already be done (with the driver options) if you have an nvidia card like GeForce.<br>* Display only available roms in the table. Note: You can sort by the first column and have your available games on top. You can have a second sorting criterion by shift+clicking on the table column.<br>* Mail me for ideas |
| **Screenshot (v0.4)** |
| [![smfe screenshot](smfe.png)](smfe.png)  <br>Click image to view the full-size capture. |
| **News** |
| * **26/Jun/2005:**version 0.12. Fixed bugs/typos, changed how verifysets is called, improved (hopefully) menu layout, fixed a bug which prevented games to start after a search for their name was performed.<br>* **30/Sep/2004:**version 0.9. Now working with mame 0.83, nplayers.ini support + small bug fixes<br>* **02/Sep/2002:**version 0.7. Fixed bugs with input devices. Thanks to Ric Kalford for the bug report.<br>* **23/Jul/2002:**version 0.6. 2 new menu options: 1) autosave "played" field is now optional to improve loading times and 2) "save table data now". Fixed "save colun sizes" (hopefully). Added an "Auto fill" button when setting the executable/image/rom paths. Added new column: "Game Category"<br>* **18/Jul/2002:**version 0.5. bug fixes + support for read-only media + display romset statistics + more debug output in console window<br>* **04/Sep/2001:**version 0.4. Changed gamelist retrieve timeout + minor bug fixes<br>* **04/Sep/2001:**Project progress will be delayed until 15 September due to other work.<br>* **25/Aug/2001:**8402 page hits, 1200 downloads so far! unbelievable!<br>* **19/Aug/2001:**version 0.3. First public version. Added some confirmation menus + screen resolution restoration code + minor bug fixes<br>* **16/Aug/2001:**version 0.2. First public SMFE release (with announcement to freshmeat)<br>* **09/Aug/2001:**Started writing the program. |
| **Links** |
| * [MAME](http://www.mame.net)<br>* [Emuloader](http://www.mameworld.net/emuloader/), another frontend, very good.<br>* [www.mame.dk](http://www.mame.dk/) arcade rom and information repository. |

  

  
Back to my [homepage](http://www.softlab.ece.ntua.gr/~sivann/)
