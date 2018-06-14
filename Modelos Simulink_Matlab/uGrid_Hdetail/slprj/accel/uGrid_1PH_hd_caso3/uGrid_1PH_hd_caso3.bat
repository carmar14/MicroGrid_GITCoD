@echo off
set MATLAB=C:\Program Files\MATLAB\R2017a
"%MATLAB%\bin\win64\gmake" -f uGrid_1PH_hd_caso3.mk  ISPROTECTINGMODEL=NOTPROTECTING
