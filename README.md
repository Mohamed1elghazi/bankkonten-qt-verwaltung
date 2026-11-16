# Bankkonten Datenbank-Verwaltung (Qt / C++)

Eine Desktop-Anwendung zur Verwaltung einer lokalen MySQL-Datenbank (`bankkonten`), entwickelt mit **C++** und **Qt 6.2**.

## Funktionen
- **Login-Dialog:** Abfrage von Kennnummer und Passwort (mit MD5-Hashing).
- **Tabellen-Übersicht:** Automatische Auflistung aller Datenbanktabellen in einer Baumansicht.
- **Tab-Ansicht:** Gleichzeitiges Öffnen mehrerer Tabellen mit Sortierfunktion und manueller Speicher-/Verwerfen-Logik (`Submit` / `Revert`).
- **Dynamische Werkzeuge:** Spalten ein-/ausblenden, Datensätze filtern und neue Zeilen über generierte Formulare hinzufügen.

## Voraussetzungen
- Qt 6.x (Widgets & SQL Modul)
- MySQL-Datenbank (Standard-Konfiguration im Code: Port `3307`, Datenbank `bankkonten`)
