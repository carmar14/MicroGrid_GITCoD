  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
      section.nData     = 73;
      section.data(73)  = dumData; %prealloc
      
	  ;% rtP.Battery_BatType
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Battery_SOC
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Constant1_Value
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Constant_Value
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.Saturation3_UpperSat
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.Saturation3_LowerSat
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.Constant10_Value
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtP.Switch3_Threshold
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtP.itinit1_X0
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtP.Constant13_Value
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtP.Switch5_Threshold
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtP.R2_Gain
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtP.Currentfilter_A
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtP.Currentfilter_C
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtP.Constant_Value_p2zc2q4ikw
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtP.inti_UpperSat
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtP.inti_LowerSat
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtP.Gain_Gain
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtP.Constant9_Value
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtP.StateSpace_A
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtP.StateSpace_B
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtP.StateSpace_C
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtP.StateSpace_X0
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtP.Constant5_Value
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtP.Constant4_Value
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% rtP.Switch_Threshold
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% rtP.Constant4_Value_hydcaj2m2n
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
	  ;% rtP.R3_Gain
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 27;
	
	  ;% rtP.Constant_Value_jasz3ij2ce
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 28;
	
	  ;% rtP.Constant1_Value_pwvdqzuhdu
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 29;
	
	  ;% rtP.Constant3_Value
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 30;
	
	  ;% rtP.Constant2_Value
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 31;
	
	  ;% rtP.Constant14_Value
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 32;
	
	  ;% rtP.Constant15_Value
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 33;
	
	  ;% rtP.Constant16_Value
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 34;
	
	  ;% rtP.Switch6_Threshold
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 35;
	
	  ;% rtP.Currentfilter1_A
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 36;
	
	  ;% rtP.Currentfilter1_C
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 37;
	
	  ;% rtP.Constant7_Value
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 38;
	
	  ;% rtP.Constant6_Value
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 39;
	
	  ;% rtP.Switch2_Threshold
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 40;
	
	  ;% rtP.Constant3_Value_hnmpswvc50
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 41;
	
	  ;% rtP.Constant2_Value_fu1vg5kur3
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 42;
	
	  ;% rtP.Switch1_Threshold
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 43;
	
	  ;% rtP.R1_Gain
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 44;
	
	  ;% rtP.StateSpace_P1_Size
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 45;
	
	  ;% rtP.StateSpace_P1
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 47;
	
	  ;% rtP.StateSpace_P2_Size
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 49;
	
	  ;% rtP.StateSpace_P2
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 51;
	
	  ;% rtP.StateSpace_P3_Size
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 55;
	
	  ;% rtP.StateSpace_P4_Size
	  section.data(51).logicalSrcIdx = 51;
	  section.data(51).dtTransOffset = 57;
	
	  ;% rtP.StateSpace_P4
	  section.data(52).logicalSrcIdx = 52;
	  section.data(52).dtTransOffset = 59;
	
	  ;% rtP.R4_Gain
	  section.data(53).logicalSrcIdx = 53;
	  section.data(53).dtTransOffset = 135;
	
	  ;% rtP.Saturation_UpperSat
	  section.data(54).logicalSrcIdx = 54;
	  section.data(54).dtTransOffset = 136;
	
	  ;% rtP.Saturation_LowerSat
	  section.data(55).logicalSrcIdx = 55;
	  section.data(55).dtTransOffset = 137;
	
	  ;% rtP.donotdeletethisgain_Gain
	  section.data(56).logicalSrcIdx = 56;
	  section.data(56).dtTransOffset = 138;
	
	  ;% rtP.R_Gain
	  section.data(57).logicalSrcIdx = 57;
	  section.data(57).dtTransOffset = 139;
	
	  ;% rtP.Constant11_Value
	  section.data(58).logicalSrcIdx = 58;
	  section.data(58).dtTransOffset = 140;
	
	  ;% rtP.Constant12_Value
	  section.data(59).logicalSrcIdx = 59;
	  section.data(59).dtTransOffset = 141;
	
	  ;% rtP.Constant8_Value
	  section.data(60).logicalSrcIdx = 60;
	  section.data(60).dtTransOffset = 142;
	
	  ;% rtP.Constant_Value_du0mfnud24
	  section.data(61).logicalSrcIdx = 61;
	  section.data(61).dtTransOffset = 143;
	
	  ;% rtP.Gain4_Gain
	  section.data(62).logicalSrcIdx = 62;
	  section.data(62).dtTransOffset = 144;
	
	  ;% rtP.Gain1_Gain
	  section.data(63).logicalSrcIdx = 63;
	  section.data(63).dtTransOffset = 145;
	
	  ;% rtP.Ta_Value
	  section.data(64).logicalSrcIdx = 64;
	  section.data(64).dtTransOffset = 146;
	
	  ;% rtP.Gain2_Gain
	  section.data(65).logicalSrcIdx = 65;
	  section.data(65).dtTransOffset = 147;
	
	  ;% rtP.Constant_Value_komnaibfv4
	  section.data(66).logicalSrcIdx = 66;
	  section.data(66).dtTransOffset = 148;
	
	  ;% rtP.Gain_Gain_mjibw0ln1h
	  section.data(67).logicalSrcIdx = 67;
	  section.data(67).dtTransOffset = 149;
	
	  ;% rtP.Saturation2_UpperSat
	  section.data(68).logicalSrcIdx = 68;
	  section.data(68).dtTransOffset = 150;
	
	  ;% rtP.Saturation2_LowerSat
	  section.data(69).logicalSrcIdx = 69;
	  section.data(69).dtTransOffset = 151;
	
	  ;% rtP.Switch4_Threshold
	  section.data(70).logicalSrcIdx = 70;
	  section.data(70).dtTransOffset = 152;
	
	  ;% rtP.TransferFcn1_A
	  section.data(71).logicalSrcIdx = 71;
	  section.data(71).dtTransOffset = 153;
	
	  ;% rtP.TransferFcn1_C
	  section.data(72).logicalSrcIdx = 72;
	  section.data(72).dtTransOffset = 154;
	
	  ;% rtP.Gain_Gain_cmwuiiiv5p
	  section.data(73).logicalSrcIdx = 73;
	  section.data(73).dtTransOffset = 155;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 59;
      section.data(59)  = dumData; %prealloc
      
	  ;% rtB.g2lfefk4ds
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.bt2plqj3b5
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.ma1gbsm4cy
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.ebowq5sonn
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.fynfg4qnb2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.dmmlw2nd0d
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.bw41kxrfxz
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.c5jq2xkgww
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.erussgeov3
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.mo54mkczvc
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.a22syqczrq
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtB.je22l4jstn
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtB.mudcvl2ext
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtB.m01gvlvnul
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtB.elvc342g14
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtB.hf3fvjualj
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtB.nwsnm0uvqi
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtB.es0vlsy1wt
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtB.mwnu2z0rpd
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtB.pxtchs05eq
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtB.dwvjnb2xhx
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtB.eyraygkx4f
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtB.elhmuoudrv
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtB.kzdncfvtsn
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtB.ebb4hiezly
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% rtB.joc3hf0wo0
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
	  ;% rtB.on5gayhq2w
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 26;
	
	  ;% rtB.lamriwhcak
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 27;
	
	  ;% rtB.ekfsltdwds
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 28;
	
	  ;% rtB.e3bmmc32eb
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 29;
	
	  ;% rtB.fiyfz5l1sl
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 30;
	
	  ;% rtB.j0kccpo40y
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 31;
	
	  ;% rtB.gxdcwqrrsh
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 32;
	
	  ;% rtB.ij4ybcvdzr
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 33;
	
	  ;% rtB.jafblclliz
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 34;
	
	  ;% rtB.jfiirh11in
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 35;
	
	  ;% rtB.pttz2gwc5w
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 36;
	
	  ;% rtB.m4wcbi2vcn
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 37;
	
	  ;% rtB.jxnoo5kkuk
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 38;
	
	  ;% rtB.hxxgeb0kvn
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 39;
	
	  ;% rtB.ppixwtawnh
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 40;
	
	  ;% rtB.g2m0yn3eet
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 41;
	
	  ;% rtB.jm4ld54oiu
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 42;
	
	  ;% rtB.hvx1f2uin3
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 43;
	
	  ;% rtB.ef1wyi5uxj
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 44;
	
	  ;% rtB.e2tlfskas5
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 45;
	
	  ;% rtB.pflv2pvbva
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 46;
	
	  ;% rtB.iluhumf0tr
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 47;
	
	  ;% rtB.nrpzodws0y
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 48;
	
	  ;% rtB.dsh3mckcs4
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 49;
	
	  ;% rtB.bdsiyxiodl
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 50;
	
	  ;% rtB.j0rbw5nmli
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 51;
	
	  ;% rtB.aacgi45bew
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 52;
	
	  ;% rtB.eladaqt13z
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 53;
	
	  ;% rtB.il5fz1koxx
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 54;
	
	  ;% rtB.ktmggdomvz
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 55;
	
	  ;% rtB.hm3jmuqecu
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 59;
	
	  ;% rtB.lqsoqxpsum
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 63;
	
	  ;% rtB.ms1eeflxuz
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 67;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% rtB.a1uqba15nh
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.f3rfg1yrey
	  section.data(2).logicalSrcIdx = 60;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.pydatjc2iu
	  section.data(3).logicalSrcIdx = 61;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.c0r3d03wfe
	  section.data(4).logicalSrcIdx = 62;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.gmzkvvbvj2
	  section.data(5).logicalSrcIdx = 63;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.bzzsqio3rp
	  section.data(6).logicalSrcIdx = 64;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 2;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDW)
    ;%
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtDW.p2ftzle2kh
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.lpgkirwqtj
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.odqq3mhlpq
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% rtDW.iq0kexwq1k
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.pktighfbvb.LoggedData
	  section.data(2).logicalSrcIdx = 4;
	  section.data(2).dtTransOffset = 22;
	
	  ;% rtDW.fqs1qzdhi3.LoggedData
	  section.data(3).logicalSrcIdx = 5;
	  section.data(3).dtTransOffset = 23;
	
	  ;% rtDW.a3eb3o3lyi.LoggedData
	  section.data(4).logicalSrcIdx = 6;
	  section.data(4).dtTransOffset = 24;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% rtDW.jxsdzjlqos
	  section.data(1).logicalSrcIdx = 7;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ppp2lay1vj
	  section.data(2).logicalSrcIdx = 8;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.p1jdd10qxn
	  section.data(3).logicalSrcIdx = 9;
	  section.data(3).dtTransOffset = 24;
	
	  ;% rtDW.b05sp2vsim
	  section.data(4).logicalSrcIdx = 10;
	  section.data(4).dtTransOffset = 25;
	
	  ;% rtDW.gyqpteeoex
	  section.data(5).logicalSrcIdx = 11;
	  section.data(5).dtTransOffset = 26;
	
	  ;% rtDW.bzypwwlvga
	  section.data(6).logicalSrcIdx = 12;
	  section.data(6).dtTransOffset = 27;
	
	  ;% rtDW.e1543zebxq
	  section.data(7).logicalSrcIdx = 13;
	  section.data(7).dtTransOffset = 28;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% rtDW.oefvsvaz2k
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.dklzoi34ek
	  section.data(2).logicalSrcIdx = 15;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.iwo5yqlhyc
	  section.data(3).logicalSrcIdx = 16;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.el333hwlaj
	  section.data(4).logicalSrcIdx = 17;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.l4j1iptt5t
	  section.data(5).logicalSrcIdx = 18;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.lwllecwx5p
	  section.data(6).logicalSrcIdx = 19;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.cjsskodlo5
	  section.data(7).logicalSrcIdx = 20;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.llhrra1e5s
	  section.data(8).logicalSrcIdx = 21;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.fh54cpx1bp
	  section.data(9).logicalSrcIdx = 22;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.ndfhbdjwe5
	  section.data(10).logicalSrcIdx = 23;
	  section.data(10).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 1145925490;
  targMap.checksum1 = 2449178161;
  targMap.checksum2 = 666433519;
  targMap.checksum3 = 3057029575;

