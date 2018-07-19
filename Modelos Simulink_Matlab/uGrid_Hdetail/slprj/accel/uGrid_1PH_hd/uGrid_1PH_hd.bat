@echo off
set MATLAB=D:\Program Files\MATLAB\R2017a
"%MATLAB%\bin\win64\gmake" -f uGrid_1PH_hd.mk  ISPROTECTINGMODEL=NOTPROTECTING
