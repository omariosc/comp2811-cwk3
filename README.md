# COMP2811 CW3 - Group 19

## Introduction

COMP2811 User Interfaces Coursework 3 - The Process. This project invloved creating a prototype for a fictional app called "Tomeo".

## How to Run

1. Download Qt 5.13.2 (must be 5.13.2) and Qt Creator from `https://www.qt.io/download-qt-installer`
2. Clone the repository  using `git clone https://github.com/omariosc/comp2811-cwk3.git`
3. Create a folder of video files called `videos` and place it in the repository folder (see Notes regarding video folder)
4. Open `the.pro` in Qt Creator and configure the project
5. Add the command line argument (to the run tab in Qt Creator) `"path/to/videos"`
6. To add video metadata, create a file for the video called `videoname.metadata` where `videoname` is the exact name of the video in the `videos` directory containing the metadata
7. The metadata should be in the following format: `Date,Length,City,CountryCode`. Where date is in the format `dd/MM/yyyy`, length in seconds, city in caps and country code in caps as a 2 letter code. For example: `15/12/2021,15,SNOWDON,UK`
8. Run the project
9. To run different iterations, open the folder in terminal and run `git checkout iteration-n`. Reload the project in QtCreator and run

## Notes
- When running on Linux, you need to ensure that all media codecs are installed (including Ubuntu Restricted Extras on Ubuntu)
- The map feature will not work unless you have OpenSSL installed
- OpenSSL (Windows Installation) through `https://www.openssl.org/`
- OpenSSL (Linux Installation) using the following command `sudo apt-get openssl`. You can check if you have OpenSSL installed using `openssl version`
- OpenSSL can also be installed through the QtCreator Maintenance Tool under Select Components > Qt > Developer and Designer Tools > OpenSSL 1.1.1j Toolkit
- We have supplied a sample video folder containing some sample videos, video thumbnails and video metadata files. Feel free to remove videos, however, the app requires at least 4 videos to function to properly. Even if you use this folder you must still pass the location for step 5
