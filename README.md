<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0f172a,50:1d4ed8,100:06b6d4&height=165&section=header&text=Portal%20Management%20System&fontSize=34&fontColor=ffffff&fontAlignY=36&desc=C%20Student%20and%20Course%20Record%20Manager&descAlignY=58&descSize=15" alt="Portal Management System" width="100%" />

**A procedural C application for managing student profiles and course enrollment records.**

<img src="https://img.shields.io/badge/C-Procedural%20Programming-A8B9CC?style=for-the-badge&logo=c&logoColor=black" alt="C" />
<img src="https://img.shields.io/badge/Storage-CSV--style%20Text%20Files-06B6D4?style=for-the-badge" alt="Text-file storage" />
<img src="https://img.shields.io/badge/Interface-Console-1D4ED8?style=for-the-badge" alt="Console interface" />

</div>

## Overview

Portal Management System is a console-based C program for maintaining student details and their course records. It uses fixed-size arrays, structures, and comma-separated text files to load data at startup and persist changes throughout the session.

## Features

- Administrator login with five attempts.
- Add students with ID, name, email, phone, and one to four courses.
- View all students or search for one student by ID.
- Edit student contact details and enrolled-course information.
- Delete individual students and their associated courses.
- Delete all student and course records.
- Load and save data through `students.txt` and `courses.txt`.

## Project Structure

```text
Portal-Management-System/
├── portalmanagement.c      # Complete application source
├── students.txt            # Persisted student records
├── courses.txt             # Persisted enrollment records
├── portalmanagement.exe    # Included Windows executable
└── README.md
```

## Build and Run

The source includes `conio.h` and Windows console commands, so a Windows-oriented C toolchain such as MinGW is recommended.

```powershell
git clone https://github.com/FarisDosani/Portal-Management-System.git
cd Portal-Management-System

gcc portalmanagement.c -o portalmanagement.exe
.\portalmanagement.exe
```

Keep `students.txt` and `courses.txt` in the working directory. If either file is missing, the application starts with no records for that data type.

## Default Login

```text
Username: portal
Password: pflab
```

These credentials are compiled into the source and are intended for coursework demonstration, not production authentication.

---

<div align="center">

<a href="https://github.com/FarisDosani/Portal-Management-System">View repository</a>

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0f172a,50:1d4ed8,100:06b6d4&height=80&section=footer" alt="" width="100%" />

</div>
