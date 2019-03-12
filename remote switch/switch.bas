! Begin by opening Bluetooth
! If Bluetooth is not enabled
! the program will stop here.

BT.OPEN

! When BT is opened, the program
! will start listening for another
! device to connect. At this time
! the user can continue to wait
! for a connection are can attempt
! to connect to another device
! that is waiting for a connection

! Ask user what to do

ARRAY.LOAD type$[], "Connect to Bluetooth", "Quit"
title$ = "Select operation mode"

new_connection:
DIALOG.SELECT type, type$[], title$

! If the user pressed the back
! key or selected quit then quit
! otherwise try to connect to
! a listener

IF (type = 0) | (type =2)
 PRINT "Thanks for playing"
 BT.CLOSE
 END
ELSEIF type = 1
 BT.CONNECT
ENDIF

! Read status until
! a connection is made

ln = 0
DO
 BT.STATUS s
 IF s = 1
  ln = ln + 1
  PRINT "Listening", ln
 ELSEIF s =2
  PRINT "Connecting"
 ELSEIF s = 3
  PRINT "Connected"
  !PRINT "Touch any text line to disconnect or quit."
  !TONE 400,100
 ENDIF
 PAUSE 1000

UNTIL s = 3

! When a connection is made
! get the name of the connected
! device

BT.DEVICE.NAME device$

! *** Read Loop ****

RW_Loop:
Console.title "APP SWITCH"
DO

 ! Read status to insure
 ! that we remain connected.
 ! If disconnected, program
 ! reverts to listen mode.
 ! In that case, ask user
 ! what to do.

 BT.STATUS s
 IF s<> 3
  PRINT "Connection lost"
  GOTO new_connection
 ENDIF

 ! Read messages until
 ! the message queue is
 ! empty
 !App.start <action_sexp>, <data_uri_sexp>, <package_sexp>, <component_sexp>,
 ! <mime_type_sexp>, <categories_sexp>, <extras_bptr_nexp>, <flags_nexp>
 
 DO
  BT.READ.READY rr
  IF rr
  BT.READ.BYTES rmsg$
	IF ASCII(rmsg$) = 5
	? "input 5"
	APP.START "android.intent.action.MAIN", , "com.android.camera2", "com.android.camera2.Camera"
	ELSEIF ASCII(rmsg$) = 6
	? "input 6"
	APP.START , , "com.android.calculator2", "com.android.calculator2.Calculator"
	ELSEIF ASCII(rmsg$) = 7
	? "input 7"
	APP.START "android.intent.action.VIEW", "http://www.mfprojects.co.uk"
	ELSEIF ASCII(rmsg$) = 8
	? "input 8"
	APP.START , , "com.google.android.gm", "com.google.android.gm.Login" 
	!APP.START , , "com.android.calculator2", "com.android.calculator2.Calculator"  
	ENDIF
  
  ENDIF
 UNTIL rr = 0
!PAUSE 1000
UNTIL 0


!RETURN
onError:
END


