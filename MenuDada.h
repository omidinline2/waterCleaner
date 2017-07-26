#ifndef _cd_timer_menu_
#define _cd_timer_menu_
#include "MenuManager.h"
#include <avr/pgmspace.h>

/*
Generated using LCD Menu Builder at http://lcd-menu-bulder.cohesivecomputing.co.uk/.
*/

enum cd_timer_menuCommandId
{
  mnuCmdBack = 0,
  mnuCmdTimer1Root,
  mnuCmdT1Hours,
  mnuCmdT1Mins,
  mnuCmdT1Secs,
  mnuCmdTimer2Root,
  mnuCmdT2Hours,
  mnuCmdT2Mins,
  mnuCmdT2Secs,
  mnuCmdTimer3Root,
  mnuCmdT3Hours,
  mnuCmdT3Mins,
  mnuCmdT3Secs,
  mnuCmdAlarmDuration,
   mnuCmdAlarmDuration2,
    mnuCmdAlarmDuration3,
     mnuCmdAlarmDuration4,
  mnuCmdButtonBeep,
  mnuCmdDisplayBrightness,
  mnuCmdResetToDefaults
};

PROGMEM const char cd_timer_menu_back[] = "Back";
PROGMEM const char cd_timer_menu_exit[] = "Exit";
 
PROGMEM const char cd_timer_menu_1[] = "Timer1 Profile";
PROGMEM const char cd_timer_menu_2[] = "Timer2 Profile";
PROGMEM const char cd_timer_menu_3[] = "Timer3 Profile";
PROGMEM const char cd_timer_menu_4[] = "Air and DC Time:";
PROGMEM const char cd_timer_menu_42[] = "Back Wash 1 Time:";
PROGMEM const char cd_timer_menu_43[] = "Back Wash 2 Time:";
PROGMEM const char cd_timer_menu_44[] = "Output Water Time:";

PROGMEM const char cd_timer_menu_5[] = "Button Beep";
PROGMEM const char cd_timer_menu_6[] = "LCD backlight";
PROGMEM const char cd_timer_menu_7[] = "Reset";
PROGMEM const MenuItem cd_timer_menu_Root[] = {   {mnuCmdAlarmDuration, cd_timer_menu_4},{mnuCmdAlarmDuration2, cd_timer_menu_42},{mnuCmdAlarmDuration3, cd_timer_menu_43},{mnuCmdAlarmDuration4, cd_timer_menu_44}, {mnuCmdButtonBeep, cd_timer_menu_5}, {mnuCmdDisplayBrightness, cd_timer_menu_6}, {mnuCmdResetToDefaults, cd_timer_menu_7}, {mnuCmdBack, cd_timer_menu_exit}};

/*
case mnuCmdT1Hours :
  break;
case mnuCmdT1Mins :
  break;
case mnuCmdT1Secs :
  break;
case mnuCmdT2Hours :
  break;
case mnuCmdT2Mins :
  break;
case mnuCmdT2Secs :
  break;
case mnuCmdT3Hours :
  break;
case mnuCmdT3Mins :
  break;
case mnuCmdT3Secs :
  break;
case mnuCmdAlarmDuration :
  break;
case mnuCmdButtonBeep :
  break;
case mnuCmdDisplayBrightness :
  break;
case mnuCmdResetToDefaults :
  break;
*/

/*
<?xml version="1.0"?>
<RootMenu xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
<!--
Addition or removal of menu items will require method processMenuCommand() in
the main project file to be modified accordingly.
-->
<Config IdPrefix="mnuCmd" VarPrefix="cd_timer_menu" UseNumbering="false" IncludeNumberHierarchy="false"
          MaxNameLen="15" MenuBackFirstItem="false" BackText="Back" ExitText="Exit" AvrProgMem="true"/>
  <MenuItems>
    <Item Id="Timer1Root" Name="Timer1 Profile">
      <MenuItems>
        <Item Id="T1Hours" Name="Timer1 set hrs"/>
        <Item Id="T1Mins" Name="Timer1 set mins"/>
        <Item Id="T1Secs" Name="Timer1 set secs"/>
      </MenuItems>
    </Item>
    <Item Id="Timer2Root" Name="Timer2 Profile">
      <MenuItems>
        <Item Id="T2Hours" Name="Timer2 set hrs"/>
        <Item Id="T2Mins" Name="Timer2 set mins"/>
        <Item Id="T2Secs" Name="Timer2 set secs"/>
      </MenuItems>
    </Item>
    <Item Id="Timer3Root" Name="Timer3 Profile">
      <MenuItems>
        <Item Id="T3Hours" Name="Timer3 set hrs"/>
        <Item Id="T3Mins" Name="Timer3 set mins"/>
        <Item Id="T3Secs" Name="Timer3 set secs"/>
      </MenuItems>
    </Item>
    <Item Id="AlarmDuration" Name="Alarm Duration"/>
    <Item Id="ButtonBeep" Name="Button Beep"/>
    <Item Id="DisplayBrightness" Name="LCD backlight"/>
    <Item Id="ResetToDefaults" Name="Reset"/>
  </MenuItems>
</RootMenu>
*/
#endif
