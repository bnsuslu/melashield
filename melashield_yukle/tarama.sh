#!/bin/bash
source $HOME/geant4/install/bin/geant4.sh

SRC=$HOME/melashield/src/DetectorConstruction.cc
BUILD=$HOME/melashield/build
OUT=$HOME/melashield/tarama_sonuclari.csv

echo "malzeme,alansal_g_cm2,kalinlik_cm,doz,doz_birim,rms,rms_birim" > $OUT

for MAT in melanin aluminium polyeth; do
  for AD in 1.0 2.0 3.0 5.0 7.0 15.0 20.0; do
    sed -i "s/shieldMat = [a-z]*;/shieldMat = $MAT;/" $SRC
    sed -i "s/arealDensity = [0-9.]*\*g/arealDensity = $AD*g/" $SRC

    cd $BUILD
    make -j4 > /dev/null 2>&1

    CIKTI=$(./exampleB1 mela.mac 2>&1 | grep -iE "KALKAN|dose")
    KAL=$(echo "$CIKTI" | grep KALKAN | sed 's/.*kalinlik \([0-9.]*\) cm.*/\1/')
    DOZ=$(echo "$CIKTI" | grep -i dose | awk '{print $9","$10","$13","$14}')

    echo "$MAT $AD g/cm2 -> $DOZ"
    echo "$MAT,$AD,$KAL,$DOZ" >> $OUT
  done
done

echo "BITTI. Sonuclar: $OUT"
