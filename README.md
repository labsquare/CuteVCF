# CuteVCF ![Travis](https://api.travis-ci.org/labsquare/CuteVCF.svg?branch=master)
simple GUI viewer for [vcf file](https://samtools.github.io/hts-specs/VCFv4.2.pdf) (variant call format) using htslib. 

![preview](https://raw.githubusercontent.com/labsquare/CuteVCF/master/preview.gif)

## Prerequis 
### Install Qt >5.7

**From Qt website** : 
Download Qt > 5.7 from https://www.qt.io/.   
Don't forget to check QtChart module during installation. 


**From ubuntu** : Qt 5.7 is not yet avaible with ubuntu. But you can add PPA to your software system. 
For exemple for xenial 

    sudo add-apt-repository ppa:beineri/opt-qt57-xenial
    sudo apt-get install qt57base qt57charts-no-lgpl
    source /opt/qt57/bin/qt57-env.shf

**From fedora** : Qt 5.7 is avaible

    sudo dnf install qt5-qtbase-devel qt5-qtcharts-devel 

### Compile CuteVCF
**From Qt Creator:** 
Open the CuteVcf.pro from Qt creator 
Compile it and Run it 

**From Terminal:**
Be sure you have the correct version of Qt (>5.7) by using qmake. You will find qmake in bin folder where you installed Qt. For exemple, if you installed Qt from ppa:beineri, you will find it under /opt/qt57/bin/qmake. Then launch the compilation from CuteVCF folder as follow.

     git clone --recursive git@github.com:labsquare/CuteVCF.git
     qmake --version
     qmake 
     make 
     sudo make install 
     
     


