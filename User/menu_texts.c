
#include "main.h"

char* EnglishTextTable[] = //8012dc0
{
	"CHAN.UP",
	"CHAN.DOWN",
	"VOL.UP",
	"VOL.DOWN",
	"MUX.UP",
	"MUX.DOWN",
	"No new channel found!",
	"No signal!",
	"No channel", //TEXT_ID_NO_CHANNEL
	"FAV-list full!",
	"OK",
	"Exit",
	"Menu",
	"Main menu", //TEXT_ID_MAIN_MENU
	"Up",
	"Down",
	"Delete",
	"Next",
	"Channel list", //TEXT_ID_CHANNEL_LIST
	"Settings", //TEXT_ID_SETTINGS
	"Factory reset",
	"Alarm",  //TEXT_ID_ALARM
	"Information",
	"Automatic search", //TEXT_ID_AUTOMATIC_SEARCH
	"Manual search",
	"Delete channel",
	"Manual search DAB",
	"Manual search FM",
	"Language", //TEXT_ID_LANGUAGE
	"Sleep-Timer", //TEXT_ID_SLEEP_TIMER
	"Auto-Standby", //TEXT_ID_AUTO_STANDBY
	"Continue?",
	"NO",
	"YES",
	"Deutsch", //TEXT_ID_GERMAN
	"English",
	"Volume",
	"Off", //TEXT_ID_OFF
	"On",
	"Signal information",
	"Channel:",
	"Multiplex:",
	"Frequency:",
	"Level:",
	"SNR:",
	"Error rate:",
	"Multipath:",
	"Freq.offset:",
	"Audio information",
	"Data rate:",
	"Sampl.frequency:",
	"Audio mode:",
	"Stereo separation:",
	"Product:",
	"Hardware:",
	"Software:",
	"DAB Firmware:",
	"FM Firmware:",
};

char* GermanTextTable[] = //8012ea8
{
	"KAN.OBEN",
	"KAN.NIEDER",
	"LAUT.OBEN",
	"LAUT.NIEDER",
	"MUX.OBEN",
	"MUX.NIEDER",
	"Kein neuer Sender gefunden",
	"Kein Signal!",
	"Kein Sender",
	"FAV-Liste voll!",
	"OK",
	"Zurück",
	"Menü",
	"Hauptmenü",
	"Ab",
	"Auf",
	"Löschen",
	"N.hste",
	"Senderliste",
	"Einstellungen",
	"Werkzustand",
	"Wecker",
	"Information",
	"Automatische Suche",
	"Manuelle Suche",
	"Sender löschen",
	"Manuelle Suche DAB",
	"Manuelle Suche FM",
	"Sprache",
	"Sleep-Timer",
	"Autom. Abschaltung",
	"Weiter?",
	"NEIN",
	"JA",
	"Deutsch",
	"English",
	"Lautstärke",
	"Aus",
	"Ein",
	"Empfang",
	"Sendername:",
	"Multiplex:",
	"Frequenz:",
	"Pegel:",
	"SNR:",
	"Fehlerrate:",
	"Mehrweg:",
	"Frek.offset:",
	"Audio Information",
	"Datenrate:",
	"Abtastfreq.:",
	"Audio Modus:",
	"Stereo Tren:",
	"Produkt:",
	"Hardware:",
	"Software:",
	"DAB Firmware:",
	"FM Firmware:",
};

/* 8005204 - todo */
void menu_set_language(uint8_t a)
{
   if (a == 1)
   {
      CurrentTextTable = EnglishTextTable;
   }
   else
   {
      CurrentTextTable = GermanTextTable;
   }
}

