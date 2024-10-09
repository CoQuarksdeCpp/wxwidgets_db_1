# TV Series and Movie Tracker

## Overview

TV Series and Movie Tracker is a desktop application built with **wxWidgets** and **SQLite3**. It allows users to manage and track information about their favorite TV series and movies, including episodes, release dates, studios, and more. The app also provides a watchlist feature, search capabilities, and detailed statistics to help users keep track of their watched and upcoming content.

## Features

- **TV Series Management**: Add, edit, view, and delete TV series information.
  - Track title, season, episode, studio, release date, next release date, and reference links.
- **Movie Management**: Add, edit, view, and delete movie information.
  - Track title, studio, release date, year, and reference links.
- **Watchlist**: Keep track of upcoming TV series episodes or movies in your watchlist.
- **Search Functionality**: Search by title, studio, release date, and more.
- **Statistics**: Get insights on your watching habits, including total watched, favorite genres, and upcoming releases.
- **Export Data**: Export your TV series and movie data to a CSV file for backup or external use.

## Installation

### Prerequisites
- **wxWidgets**: The application is built using wxWidgets for the GUI.
- **SQLite3**: The app uses SQLite3 to store TV series and movie data locally.

Ensure you have wxWidgets and SQLite3 installed on your system. You can install these dependencies via your package manager (or with vcpkg for Visual Studio users):

```bash
# Install wxWidgets and SQLite3 via vcpkg (for Visual Studio users)
vcpkg install wxwidgets sqlite3
