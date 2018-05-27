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
      section.nData     = 241;
      section.data(241)  = dumData; %prealloc
      
	  ;% rtP.G
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.GF
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 40000;
	
	  ;% rtP.DC_2_Amplitude
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 80000;
	
	  ;% rtP.DC540V_Amplitude
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 80001;
	
	  ;% rtP.DC_1_Amplitude
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 80002;
	
	  ;% rtP.uPh_Inverter_bio_st_time
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 80003;
	
	  ;% rtP.uPh_Inverter_diesel_st_time
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 80004;
	
	  ;% rtP.uPh_Inverter_bio1_st_time
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 80005;
	
	  ;% rtP.eee_Value
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 80006;
	
	  ;% rtP.eee_Value_kjv1lt1rls
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 80007;
	
	  ;% rtP.eee_Value_luohiy4ktt
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 80008;
	
	  ;% rtP.eee_Value_la1sxv22ch
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 80009;
	
	  ;% rtP.eee_Value_n2jnc2ydfy
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 80010;
	
	  ;% rtP.eee_Value_eahotdmisl
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 80011;
	
	  ;% rtP.eee_Value_lkmzkp31k3
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 80012;
	
	  ;% rtP.eee_Value_akbbszpib5
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 80013;
	
	  ;% rtP.eee_Value_cnrsszzthq
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 80014;
	
	  ;% rtP.eee_Value_gv0u2ahtt0
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 80015;
	
	  ;% rtP.eee_Value_h3by2pvwt1
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 80016;
	
	  ;% rtP.eee_Value_lskvq5tfxu
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 80017;
	
	  ;% rtP.StateSpace_P1_Size
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 80018;
	
	  ;% rtP.StateSpace_P1
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 80020;
	
	  ;% rtP.StateSpace_P2_Size
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 87860;
	
	  ;% rtP.StateSpace_P2
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 87862;
	
	  ;% rtP.StateSpace_P3_Size
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 87866;
	
	  ;% rtP.StateSpace_P3
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 87868;
	
	  ;% rtP.StateSpace_P4_Size
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 87889;
	
	  ;% rtP.StateSpace_P4
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 87891;
	
	  ;% rtP.StateSpace_P5_Size
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 94891;
	
	  ;% rtP.StateSpace_P5
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 94893;
	
	  ;% rtP.StateSpace_P6_Size
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 94947;
	
	  ;% rtP.StateSpace_P6
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 94949;
	
	  ;% rtP.StateSpace_P7_Size
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 94976;
	
	  ;% rtP.StateSpace_P7
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 94978;
	
	  ;% rtP.StateSpace_P8_Size
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 95005;
	
	  ;% rtP.StateSpace_P8
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 95007;
	
	  ;% rtP.StateSpace_P9_Size
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 95034;
	
	  ;% rtP.StateSpace_P9
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 95036;
	
	  ;% rtP.StateSpace_P10_Size
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 95037;
	
	  ;% rtP.StateSpace_P10
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 95039;
	
	  ;% rtP.P_lp_bio_Value
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 95040;
	
	  ;% rtP.Constant_Value
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 95041;
	
	  ;% rtP.Step1_Time
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 95042;
	
	  ;% rtP.Step1_Y0
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 95043;
	
	  ;% rtP.Step1_YFinal
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 95044;
	
	  ;% rtP.Step2_Time
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 95045;
	
	  ;% rtP.Step2_Y0
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 95046;
	
	  ;% rtP.Step2_YFinal
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 95047;
	
	  ;% rtP.Step3_Time
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 95048;
	
	  ;% rtP.Step3_Y0
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 95049;
	
	  ;% rtP.Step3_YFinal
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 95050;
	
	  ;% rtP.Constant1_Value
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 95051;
	
	  ;% rtP.Constant5_Value
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 95052;
	
	  ;% rtP.P_lp_diesel_Value
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 95053;
	
	  ;% rtP.Hw2_A
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 95054;
	
	  ;% rtP.Hw2_B
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 95061;
	
	  ;% rtP.Hw2_C
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 95062;
	
	  ;% rtP.Hw2_X0
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 95063;
	
	  ;% rtP.Hw6_A
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 95064;
	
	  ;% rtP.Hw6_B
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 95071;
	
	  ;% rtP.Hw6_C
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 95072;
	
	  ;% rtP.Hw6_X0
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 95073;
	
	  ;% rtP.Hw1_A
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 95074;
	
	  ;% rtP.Hw1_B
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 95081;
	
	  ;% rtP.Hw1_C
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 95082;
	
	  ;% rtP.Hw1_X0
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 95083;
	
	  ;% rtP.Hw3_A
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 95084;
	
	  ;% rtP.Hw3_B
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 95091;
	
	  ;% rtP.Hw3_C
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 95092;
	
	  ;% rtP.Hw3_X0
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 95093;
	
	  ;% rtP.Hw4_A
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 95094;
	
	  ;% rtP.Hw4_B
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 95097;
	
	  ;% rtP.Hw4_C
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 95098;
	
	  ;% rtP.Hw4_X0
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 95099;
	
	  ;% rtP.Hw1_A_kbzflcjjyj
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 95100;
	
	  ;% rtP.Hw1_B_o4lzhk3gnx
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 95103;
	
	  ;% rtP.Hw1_C_i3w2ow0rwv
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 95104;
	
	  ;% rtP.Hw1_X0_jjtb1pylbl
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 95105;
	
	  ;% rtP.Hw7_A
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 95106;
	
	  ;% rtP.Hw7_B
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 95109;
	
	  ;% rtP.Hw7_C
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 95110;
	
	  ;% rtP.Hw7_X0
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 95111;
	
	  ;% rtP.Hw3_A_ngyitj1gem
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 95112;
	
	  ;% rtP.Hw3_B_mskofuv4se
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 95115;
	
	  ;% rtP.Hw3_C_mvzrzdbpid
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 95116;
	
	  ;% rtP.Hw3_X0_fiftn0ykcd
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 95117;
	
	  ;% rtP.ttkernel_P1_Size
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 95118;
	
	  ;% rtP.ttkernel_P1
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 95120;
	
	  ;% rtP.ttkernel_P2_Size
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 95128;
	
	  ;% rtP.ttkernel_P2
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 95130;
	
	  ;% rtP.ttkernel_P3_Size
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 95131;
	
	  ;% rtP.ttkernel_P3
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 95133;
	
	  ;% rtP.ttkernel_P4_Size
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 95135;
	
	  ;% rtP.ttkernel_P4
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 95137;
	
	  ;% rtP.ttkernel_P5_Size
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 95138;
	
	  ;% rtP.ttkernel_P5
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 95140;
	
	  ;% rtP.ttkernel_P6_Size
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 95141;
	
	  ;% rtP.ttkernel_P7_Size
	  section.data(98).logicalSrcIdx = 98;
	  section.data(98).dtTransOffset = 95143;
	
	  ;% rtP.ttkernel_P7
	  section.data(99).logicalSrcIdx = 99;
	  section.data(99).dtTransOffset = 95145;
	
	  ;% rtP.ttkernel_P1_Size_phmcx0huck
	  section.data(100).logicalSrcIdx = 100;
	  section.data(100).dtTransOffset = 95147;
	
	  ;% rtP.ttkernel_P1_kegxebksg2
	  section.data(101).logicalSrcIdx = 101;
	  section.data(101).dtTransOffset = 95149;
	
	  ;% rtP.ttkernel_P2_Size_nfb4tmfvso
	  section.data(102).logicalSrcIdx = 102;
	  section.data(102).dtTransOffset = 95160;
	
	  ;% rtP.ttkernel_P3_Size_ijstpct3xa
	  section.data(103).logicalSrcIdx = 104;
	  section.data(103).dtTransOffset = 95162;
	
	  ;% rtP.ttkernel_P3_gqnydskipg
	  section.data(104).logicalSrcIdx = 105;
	  section.data(104).dtTransOffset = 95164;
	
	  ;% rtP.ttkernel_P4_Size_hjw55qqsby
	  section.data(105).logicalSrcIdx = 106;
	  section.data(105).dtTransOffset = 95166;
	
	  ;% rtP.ttkernel_P4_czxg5elx0u
	  section.data(106).logicalSrcIdx = 107;
	  section.data(106).dtTransOffset = 95168;
	
	  ;% rtP.ttkernel_P5_Size_b1wzcdhzz4
	  section.data(107).logicalSrcIdx = 108;
	  section.data(107).dtTransOffset = 95169;
	
	  ;% rtP.ttkernel_P5_eeyd0jrw1c
	  section.data(108).logicalSrcIdx = 109;
	  section.data(108).dtTransOffset = 95171;
	
	  ;% rtP.ttkernel_P6_Size_dgpycuraph
	  section.data(109).logicalSrcIdx = 110;
	  section.data(109).dtTransOffset = 95172;
	
	  ;% rtP.ttkernel_P7_Size_f3wuxlprs0
	  section.data(110).logicalSrcIdx = 112;
	  section.data(110).dtTransOffset = 95174;
	
	  ;% rtP.ttkernel_P7_hxqdtrr2zt
	  section.data(111).logicalSrcIdx = 113;
	  section.data(111).dtTransOffset = 95176;
	
	  ;% rtP.donotdeletethisgain_Gain
	  section.data(112).logicalSrcIdx = 114;
	  section.data(112).dtTransOffset = 95178;
	
	  ;% rtP.TransferFcn_A
	  section.data(113).logicalSrcIdx = 115;
	  section.data(113).dtTransOffset = 95179;
	
	  ;% rtP.TransferFcn_C
	  section.data(114).logicalSrcIdx = 116;
	  section.data(114).dtTransOffset = 95180;
	
	  ;% rtP.TransferFcn1_A
	  section.data(115).logicalSrcIdx = 117;
	  section.data(115).dtTransOffset = 95181;
	
	  ;% rtP.TransferFcn1_C
	  section.data(116).logicalSrcIdx = 118;
	  section.data(116).dtTransOffset = 95182;
	
	  ;% rtP.donotdeletethisgain_Gain_khgfu0zvf4
	  section.data(117).logicalSrcIdx = 119;
	  section.data(117).dtTransOffset = 95183;
	
	  ;% rtP.gate_Value
	  section.data(118).logicalSrcIdx = 120;
	  section.data(118).dtTransOffset = 95184;
	
	  ;% rtP.gate_Value_o1atqxnff5
	  section.data(119).logicalSrcIdx = 121;
	  section.data(119).dtTransOffset = 95185;
	
	  ;% rtP.gate_Value_ivxretxarq
	  section.data(120).logicalSrcIdx = 122;
	  section.data(120).dtTransOffset = 95186;
	
	  ;% rtP.gate_Value_p51ecoshdm
	  section.data(121).logicalSrcIdx = 123;
	  section.data(121).dtTransOffset = 95187;
	
	  ;% rtP.Constant1_Value_ihao24qd3r
	  section.data(122).logicalSrcIdx = 124;
	  section.data(122).dtTransOffset = 95188;
	
	  ;% rtP.Constant_Value_j5zaiux01a
	  section.data(123).logicalSrcIdx = 125;
	  section.data(123).dtTransOffset = 95189;
	
	  ;% rtP.Constant3_Value
	  section.data(124).logicalSrcIdx = 126;
	  section.data(124).dtTransOffset = 95190;
	
	  ;% rtP.Constant2_Value
	  section.data(125).logicalSrcIdx = 127;
	  section.data(125).dtTransOffset = 95191;
	
	  ;% rtP.uib1_Gain
	  section.data(126).logicalSrcIdx = 128;
	  section.data(126).dtTransOffset = 95192;
	
	  ;% rtP.Gain_Gain
	  section.data(127).logicalSrcIdx = 129;
	  section.data(127).dtTransOffset = 95193;
	
	  ;% rtP.Step_Y0
	  section.data(128).logicalSrcIdx = 130;
	  section.data(128).dtTransOffset = 95194;
	
	  ;% rtP.Step_YFinal
	  section.data(129).logicalSrcIdx = 131;
	  section.data(129).dtTransOffset = 95195;
	
	  ;% rtP.Step_Y0_legsdikta1
	  section.data(130).logicalSrcIdx = 132;
	  section.data(130).dtTransOffset = 95196;
	
	  ;% rtP.Step_YFinal_n0k22wxmnl
	  section.data(131).logicalSrcIdx = 133;
	  section.data(131).dtTransOffset = 95197;
	
	  ;% rtP.C4_Value
	  section.data(132).logicalSrcIdx = 134;
	  section.data(132).dtTransOffset = 95198;
	
	  ;% rtP.Step_Y0_p2wkubb2bf
	  section.data(133).logicalSrcIdx = 135;
	  section.data(133).dtTransOffset = 95199;
	
	  ;% rtP.Step_YFinal_i1efzfr20g
	  section.data(134).logicalSrcIdx = 136;
	  section.data(134).dtTransOffset = 95200;
	
	  ;% rtP.LookUpTable_XData
	  section.data(135).logicalSrcIdx = 137;
	  section.data(135).dtTransOffset = 95201;
	
	  ;% rtP.LookUpTable_YData
	  section.data(136).logicalSrcIdx = 138;
	  section.data(136).dtTransOffset = 95206;
	
	  ;% rtP.Switch3_Threshold
	  section.data(137).logicalSrcIdx = 139;
	  section.data(137).dtTransOffset = 95211;
	
	  ;% rtP.HitCrossing_Offset
	  section.data(138).logicalSrcIdx = 140;
	  section.data(138).dtTransOffset = 95212;
	
	  ;% rtP.donotdeletethisgain_Gain_aqki2j0pex
	  section.data(139).logicalSrcIdx = 141;
	  section.data(139).dtTransOffset = 95213;
	
	  ;% rtP.TransferFcn_A_jmuxqs4cyv
	  section.data(140).logicalSrcIdx = 142;
	  section.data(140).dtTransOffset = 95214;
	
	  ;% rtP.TransferFcn_C_assnubnh1r
	  section.data(141).logicalSrcIdx = 143;
	  section.data(141).dtTransOffset = 95215;
	
	  ;% rtP.TransferFcn1_A_gyfo1spe1k
	  section.data(142).logicalSrcIdx = 144;
	  section.data(142).dtTransOffset = 95216;
	
	  ;% rtP.TransferFcn1_C_c0ncjvfshw
	  section.data(143).logicalSrcIdx = 145;
	  section.data(143).dtTransOffset = 95217;
	
	  ;% rtP.donotdeletethisgain_Gain_malkwg3eo0
	  section.data(144).logicalSrcIdx = 146;
	  section.data(144).dtTransOffset = 95218;
	
	  ;% rtP.gate_Value_evjry40iys
	  section.data(145).logicalSrcIdx = 147;
	  section.data(145).dtTransOffset = 95219;
	
	  ;% rtP.gate_Value_duqg5wmkuu
	  section.data(146).logicalSrcIdx = 148;
	  section.data(146).dtTransOffset = 95220;
	
	  ;% rtP.gate_Value_but4pbwkg3
	  section.data(147).logicalSrcIdx = 149;
	  section.data(147).dtTransOffset = 95221;
	
	  ;% rtP.gate_Value_jhlex4egqq
	  section.data(148).logicalSrcIdx = 150;
	  section.data(148).dtTransOffset = 95222;
	
	  ;% rtP.Constant1_Value_oo43yhpvhj
	  section.data(149).logicalSrcIdx = 151;
	  section.data(149).dtTransOffset = 95223;
	
	  ;% rtP.ttkernel_P1_Size_i4hx3ztcux
	  section.data(150).logicalSrcIdx = 152;
	  section.data(150).dtTransOffset = 95224;
	
	  ;% rtP.ttkernel_P1_dau5ffdd1u
	  section.data(151).logicalSrcIdx = 153;
	  section.data(151).dtTransOffset = 95226;
	
	  ;% rtP.ttkernel_P2_Size_mzxvmttuan
	  section.data(152).logicalSrcIdx = 154;
	  section.data(152).dtTransOffset = 95237;
	
	  ;% rtP.ttkernel_P3_Size_iim3bl5h1p
	  section.data(153).logicalSrcIdx = 156;
	  section.data(153).dtTransOffset = 95239;
	
	  ;% rtP.ttkernel_P3_alumkyzhoh
	  section.data(154).logicalSrcIdx = 157;
	  section.data(154).dtTransOffset = 95241;
	
	  ;% rtP.ttkernel_P4_Size_gchejzj5nn
	  section.data(155).logicalSrcIdx = 158;
	  section.data(155).dtTransOffset = 95243;
	
	  ;% rtP.ttkernel_P4_pykitjxifn
	  section.data(156).logicalSrcIdx = 159;
	  section.data(156).dtTransOffset = 95245;
	
	  ;% rtP.ttkernel_P5_Size_fql1qn3mk2
	  section.data(157).logicalSrcIdx = 160;
	  section.data(157).dtTransOffset = 95246;
	
	  ;% rtP.ttkernel_P5_a0o1uqg3oc
	  section.data(158).logicalSrcIdx = 161;
	  section.data(158).dtTransOffset = 95248;
	
	  ;% rtP.ttkernel_P6_Size_lwwqe3gebn
	  section.data(159).logicalSrcIdx = 162;
	  section.data(159).dtTransOffset = 95249;
	
	  ;% rtP.ttkernel_P7_Size_cn31xdj5c3
	  section.data(160).logicalSrcIdx = 164;
	  section.data(160).dtTransOffset = 95251;
	
	  ;% rtP.ttkernel_P7_gqqekjm05a
	  section.data(161).logicalSrcIdx = 165;
	  section.data(161).dtTransOffset = 95253;
	
	  ;% rtP.Constant_Value_lpxxzcor1x
	  section.data(162).logicalSrcIdx = 166;
	  section.data(162).dtTransOffset = 95255;
	
	  ;% rtP.Constant3_Value_j5dz1hgiog
	  section.data(163).logicalSrcIdx = 167;
	  section.data(163).dtTransOffset = 95256;
	
	  ;% rtP.Constant2_Value_ecraziuear
	  section.data(164).logicalSrcIdx = 168;
	  section.data(164).dtTransOffset = 95257;
	
	  ;% rtP.uib1_Gain_hysnw5mqld
	  section.data(165).logicalSrcIdx = 169;
	  section.data(165).dtTransOffset = 95258;
	
	  ;% rtP.Gain_Gain_mygr3ck4si
	  section.data(166).logicalSrcIdx = 170;
	  section.data(166).dtTransOffset = 95259;
	
	  ;% rtP.Step_Y0_nw5wkv3ooz
	  section.data(167).logicalSrcIdx = 171;
	  section.data(167).dtTransOffset = 95260;
	
	  ;% rtP.Step_YFinal_nmjbi1q1jk
	  section.data(168).logicalSrcIdx = 172;
	  section.data(168).dtTransOffset = 95261;
	
	  ;% rtP.Step_Y0_efnefifyw2
	  section.data(169).logicalSrcIdx = 173;
	  section.data(169).dtTransOffset = 95262;
	
	  ;% rtP.Step_YFinal_onn4xqhkyw
	  section.data(170).logicalSrcIdx = 174;
	  section.data(170).dtTransOffset = 95263;
	
	  ;% rtP.C4_Value_aagigtr1s1
	  section.data(171).logicalSrcIdx = 175;
	  section.data(171).dtTransOffset = 95264;
	
	  ;% rtP.Step_Y0_h0xozw0tcv
	  section.data(172).logicalSrcIdx = 176;
	  section.data(172).dtTransOffset = 95265;
	
	  ;% rtP.Step_YFinal_eksdyefhpg
	  section.data(173).logicalSrcIdx = 177;
	  section.data(173).dtTransOffset = 95266;
	
	  ;% rtP.LookUpTable_XData_h2at0lfgy0
	  section.data(174).logicalSrcIdx = 178;
	  section.data(174).dtTransOffset = 95267;
	
	  ;% rtP.LookUpTable_YData_kfsva1ia4o
	  section.data(175).logicalSrcIdx = 179;
	  section.data(175).dtTransOffset = 95272;
	
	  ;% rtP.Switch3_Threshold_obfdmxriwc
	  section.data(176).logicalSrcIdx = 180;
	  section.data(176).dtTransOffset = 95277;
	
	  ;% rtP.HitCrossing_Offset_dtlkzxqizf
	  section.data(177).logicalSrcIdx = 181;
	  section.data(177).dtTransOffset = 95278;
	
	  ;% rtP.Energy_Value
	  section.data(178).logicalSrcIdx = 182;
	  section.data(178).dtTransOffset = 95279;
	
	  ;% rtP.Energy_Value_llumdghwbm
	  section.data(179).logicalSrcIdx = 183;
	  section.data(179).dtTransOffset = 95280;
	
	  ;% rtP.Memory1_X0
	  section.data(180).logicalSrcIdx = 184;
	  section.data(180).dtTransOffset = 95281;
	
	  ;% rtP.Memory2_X0
	  section.data(181).logicalSrcIdx = 185;
	  section.data(181).dtTransOffset = 95282;
	
	  ;% rtP.Memory3_X0
	  section.data(182).logicalSrcIdx = 186;
	  section.data(182).dtTransOffset = 95283;
	
	  ;% rtP.Memory4_X0
	  section.data(183).logicalSrcIdx = 187;
	  section.data(183).dtTransOffset = 95284;
	
	  ;% rtP.Energy_Value_in0imrdvbj
	  section.data(184).logicalSrcIdx = 188;
	  section.data(184).dtTransOffset = 95285;
	
	  ;% rtP.Hw2_A_jjvwx3g4vm
	  section.data(185).logicalSrcIdx = 189;
	  section.data(185).dtTransOffset = 95286;
	
	  ;% rtP.Hw2_B_ag4uxupnle
	  section.data(186).logicalSrcIdx = 190;
	  section.data(186).dtTransOffset = 95289;
	
	  ;% rtP.Hw2_C_c1pm2juzi1
	  section.data(187).logicalSrcIdx = 191;
	  section.data(187).dtTransOffset = 95290;
	
	  ;% rtP.Hw2_X0_dwpd2y1z3s
	  section.data(188).logicalSrcIdx = 192;
	  section.data(188).dtTransOffset = 95291;
	
	  ;% rtP.donotdeletethisgain_Gain_muoknirdms
	  section.data(189).logicalSrcIdx = 193;
	  section.data(189).dtTransOffset = 95292;
	
	  ;% rtP.SwitchingFilterCapacitor1_Value
	  section.data(190).logicalSrcIdx = 194;
	  section.data(190).dtTransOffset = 95293;
	
	  ;% rtP.SineWave_Amp
	  section.data(191).logicalSrcIdx = 195;
	  section.data(191).dtTransOffset = 95294;
	
	  ;% rtP.SineWave_Bias
	  section.data(192).logicalSrcIdx = 196;
	  section.data(192).dtTransOffset = 95295;
	
	  ;% rtP.SineWave_Freq
	  section.data(193).logicalSrcIdx = 197;
	  section.data(193).dtTransOffset = 95296;
	
	  ;% rtP.SineWave_Phase
	  section.data(194).logicalSrcIdx = 198;
	  section.data(194).dtTransOffset = 95297;
	
	  ;% rtP.Hi_Pass1_A
	  section.data(195).logicalSrcIdx = 199;
	  section.data(195).dtTransOffset = 95298;
	
	  ;% rtP.Hi_Pass1_B
	  section.data(196).logicalSrcIdx = 200;
	  section.data(196).dtTransOffset = 95299;
	
	  ;% rtP.Hi_Pass1_C
	  section.data(197).logicalSrcIdx = 201;
	  section.data(197).dtTransOffset = 95300;
	
	  ;% rtP.Hi_Pass1_D
	  section.data(198).logicalSrcIdx = 202;
	  section.data(198).dtTransOffset = 95301;
	
	  ;% rtP.Hi_Pass1_X0
	  section.data(199).logicalSrcIdx = 203;
	  section.data(199).dtTransOffset = 95302;
	
	  ;% rtP.Hw5_A
	  section.data(200).logicalSrcIdx = 204;
	  section.data(200).dtTransOffset = 95303;
	
	  ;% rtP.Hw5_B
	  section.data(201).logicalSrcIdx = 205;
	  section.data(201).dtTransOffset = 95306;
	
	  ;% rtP.Hw5_C
	  section.data(202).logicalSrcIdx = 206;
	  section.data(202).dtTransOffset = 95307;
	
	  ;% rtP.Hw5_X0
	  section.data(203).logicalSrcIdx = 207;
	  section.data(203).dtTransOffset = 95308;
	
	  ;% rtP.Gain2_Gain
	  section.data(204).logicalSrcIdx = 208;
	  section.data(204).dtTransOffset = 95309;
	
	  ;% rtP.TransferFcn1_A_mhbp45m11f
	  section.data(205).logicalSrcIdx = 209;
	  section.data(205).dtTransOffset = 95310;
	
	  ;% rtP.TransferFcn1_C_d5ieeyryfz
	  section.data(206).logicalSrcIdx = 210;
	  section.data(206).dtTransOffset = 95312;
	
	  ;% rtP.Constant2_Value_bnaip2qh1m
	  section.data(207).logicalSrcIdx = 211;
	  section.data(207).dtTransOffset = 95314;
	
	  ;% rtP.Hw6_A_ljeu45oawb
	  section.data(208).logicalSrcIdx = 212;
	  section.data(208).dtTransOffset = 95315;
	
	  ;% rtP.Hw6_B_ovbhidad3v
	  section.data(209).logicalSrcIdx = 213;
	  section.data(209).dtTransOffset = 95318;
	
	  ;% rtP.Hw6_C_i2gbmjev5d
	  section.data(210).logicalSrcIdx = 214;
	  section.data(210).dtTransOffset = 95319;
	
	  ;% rtP.Hw6_X0_eqbfuwse4i
	  section.data(211).logicalSrcIdx = 215;
	  section.data(211).dtTransOffset = 95320;
	
	  ;% rtP.donotdeletethisgain_Gain_pfs1e1lqot
	  section.data(212).logicalSrcIdx = 216;
	  section.data(212).dtTransOffset = 95321;
	
	  ;% rtP.TransferFcn_A_fo4eivk0cz
	  section.data(213).logicalSrcIdx = 217;
	  section.data(213).dtTransOffset = 95322;
	
	  ;% rtP.TransferFcn_C_cidb1uzs1l
	  section.data(214).logicalSrcIdx = 218;
	  section.data(214).dtTransOffset = 95323;
	
	  ;% rtP.TransferFcn1_A_gbpccbxwkq
	  section.data(215).logicalSrcIdx = 219;
	  section.data(215).dtTransOffset = 95324;
	
	  ;% rtP.TransferFcn1_C_iymr30cu1l
	  section.data(216).logicalSrcIdx = 220;
	  section.data(216).dtTransOffset = 95325;
	
	  ;% rtP.donotdeletethisgain_Gain_gwkq5frpca
	  section.data(217).logicalSrcIdx = 221;
	  section.data(217).dtTransOffset = 95326;
	
	  ;% rtP.donotdeletethisgain_Gain_lmwc2zhiza
	  section.data(218).logicalSrcIdx = 222;
	  section.data(218).dtTransOffset = 95327;
	
	  ;% rtP.TransferFcn2_A
	  section.data(219).logicalSrcIdx = 223;
	  section.data(219).dtTransOffset = 95328;
	
	  ;% rtP.TransferFcn2_C
	  section.data(220).logicalSrcIdx = 224;
	  section.data(220).dtTransOffset = 95329;
	
	  ;% rtP.gate_Value_i5kbinpwee
	  section.data(221).logicalSrcIdx = 225;
	  section.data(221).dtTransOffset = 95330;
	
	  ;% rtP.gate_Value_bt41vtykjz
	  section.data(222).logicalSrcIdx = 226;
	  section.data(222).dtTransOffset = 95331;
	
	  ;% rtP.gate_Value_h10hkkwhs2
	  section.data(223).logicalSrcIdx = 227;
	  section.data(223).dtTransOffset = 95332;
	
	  ;% rtP.gate_Value_ojlyotiqqk
	  section.data(224).logicalSrcIdx = 228;
	  section.data(224).dtTransOffset = 95333;
	
	  ;% rtP.Constant1_Value_cqn15imi2r
	  section.data(225).logicalSrcIdx = 229;
	  section.data(225).dtTransOffset = 95334;
	
	  ;% rtP.Constant_Value_ohbjm2j0ij
	  section.data(226).logicalSrcIdx = 230;
	  section.data(226).dtTransOffset = 95335;
	
	  ;% rtP.Constant3_Value_hzs44l22rj
	  section.data(227).logicalSrcIdx = 231;
	  section.data(227).dtTransOffset = 95336;
	
	  ;% rtP.Constant2_Value_efe4bfc10e
	  section.data(228).logicalSrcIdx = 232;
	  section.data(228).dtTransOffset = 95337;
	
	  ;% rtP.uib1_Gain_buhnycyzrk
	  section.data(229).logicalSrcIdx = 233;
	  section.data(229).dtTransOffset = 95338;
	
	  ;% rtP.Gain_Gain_bktwk0ibkx
	  section.data(230).logicalSrcIdx = 234;
	  section.data(230).dtTransOffset = 95339;
	
	  ;% rtP.Step_Y0_m1xcmpkjwa
	  section.data(231).logicalSrcIdx = 235;
	  section.data(231).dtTransOffset = 95340;
	
	  ;% rtP.Step_YFinal_h3jz4xlvs5
	  section.data(232).logicalSrcIdx = 236;
	  section.data(232).dtTransOffset = 95341;
	
	  ;% rtP.Step_Y0_flotjz4byv
	  section.data(233).logicalSrcIdx = 237;
	  section.data(233).dtTransOffset = 95342;
	
	  ;% rtP.Step_YFinal_iajv2qdnwe
	  section.data(234).logicalSrcIdx = 238;
	  section.data(234).dtTransOffset = 95343;
	
	  ;% rtP.C4_Value_lgay0qrqwc
	  section.data(235).logicalSrcIdx = 239;
	  section.data(235).dtTransOffset = 95344;
	
	  ;% rtP.Step_Y0_ji235vnkbb
	  section.data(236).logicalSrcIdx = 240;
	  section.data(236).dtTransOffset = 95345;
	
	  ;% rtP.Step_YFinal_jlaji2juh5
	  section.data(237).logicalSrcIdx = 241;
	  section.data(237).dtTransOffset = 95346;
	
	  ;% rtP.LookUpTable_XData_djytinpfos
	  section.data(238).logicalSrcIdx = 242;
	  section.data(238).dtTransOffset = 95347;
	
	  ;% rtP.LookUpTable_YData_oewicl1qan
	  section.data(239).logicalSrcIdx = 243;
	  section.data(239).dtTransOffset = 95352;
	
	  ;% rtP.Switch3_Threshold_ohskz1p5nh
	  section.data(240).logicalSrcIdx = 244;
	  section.data(240).dtTransOffset = 95357;
	
	  ;% rtP.HitCrossing_Offset_ez0hdaiej5
	  section.data(241).logicalSrcIdx = 245;
	  section.data(241).dtTransOffset = 95358;
	
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
    nTotSects     = 10;
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
      section.nData     = 121;
      section.data(121)  = dumData; %prealloc
      
	  ;% rtB.eh1uxfdfxk
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.fn4ajroglo
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.le51iuyvkp
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtB.aunpobcu44
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtB.jc05hb1vpg
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtB.eczkwep1fc
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtB.haih3brbef
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtB.ddj2ljlqar
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtB.fhtkgnfwcd
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtB.mlexdgwnj1
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtB.izwvjz1tew
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtB.kjzt3xvlg4
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtB.fkqc2ypzow
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtB.dmlly3udcf
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtB.bk1xuitdvv
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtB.aqe3urztoo
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtB.bmqsiz2toy
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 23;
	
	  ;% rtB.jhuzfee1rx
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 77;
	
	  ;% rtB.d5oxoszzwe
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 78;
	
	  ;% rtB.ptnr1vtbjm
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 79;
	
	  ;% rtB.puuyej0ojx
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 80;
	
	  ;% rtB.nk2fzzksvb
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 81;
	
	  ;% rtB.gwjcoav1lk
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 82;
	
	  ;% rtB.b1utvav4hj
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 83;
	
	  ;% rtB.btdi3tstnl
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 84;
	
	  ;% rtB.iq42atba5o
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 85;
	
	  ;% rtB.m1it3g5wdk
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 86;
	
	  ;% rtB.cypxcf4iuh
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 87;
	
	  ;% rtB.cr3o3bcjno
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 88;
	
	  ;% rtB.i0tzocdcou
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 89;
	
	  ;% rtB.hbd0hneu5u
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 90;
	
	  ;% rtB.o3zd3lrgcz
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 93;
	
	  ;% rtB.hxnhqtjvzy
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 94;
	
	  ;% rtB.o3l2gemtct
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 95;
	
	  ;% rtB.lmlfl3t04h
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 96;
	
	  ;% rtB.ewo1cwunpw
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 100;
	
	  ;% rtB.m4dlwah4c3
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 101;
	
	  ;% rtB.jvajaeojzw
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 102;
	
	  ;% rtB.jr3vymwmkc
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 103;
	
	  ;% rtB.l2k5p2r0wh
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 104;
	
	  ;% rtB.d4o1qxqtvz
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 105;
	
	  ;% rtB.obugd5y2ad
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 106;
	
	  ;% rtB.hbhwwpohe0
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 107;
	
	  ;% rtB.bbzwoxa50q
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 108;
	
	  ;% rtB.cao3opsb5y
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 109;
	
	  ;% rtB.f2y40zjr03
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 110;
	
	  ;% rtB.jvnydmoxuc
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 111;
	
	  ;% rtB.dbr0navviv
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 112;
	
	  ;% rtB.hsj4xty3ld
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 113;
	
	  ;% rtB.j1nlrdh0gl
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 114;
	
	  ;% rtB.oe0msxmkyu
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 115;
	
	  ;% rtB.du31rtbcg2
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 116;
	
	  ;% rtB.aoljwchi5z
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 117;
	
	  ;% rtB.pfa5sut0yt
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 118;
	
	  ;% rtB.chc3tp5kgw
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 119;
	
	  ;% rtB.pgxj3vimkq
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 120;
	
	  ;% rtB.hchtpl1d3p
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 121;
	
	  ;% rtB.ke5galvxnd
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 122;
	
	  ;% rtB.njnf2oxsm1
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 123;
	
	  ;% rtB.bivhyu0fbz
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 124;
	
	  ;% rtB.m1ekwvon4u
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 125;
	
	  ;% rtB.gxoc5j0ev2
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 126;
	
	  ;% rtB.czdizqkiy5
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 129;
	
	  ;% rtB.kam4wd2zke
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 130;
	
	  ;% rtB.pzlqwcc3xg
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 131;
	
	  ;% rtB.aeiozt25lb
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 132;
	
	  ;% rtB.posuhuud3g
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 133;
	
	  ;% rtB.bu3zpefbt0
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 134;
	
	  ;% rtB.hilnaqgqvk
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 135;
	
	  ;% rtB.cvy5dhiqlw
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 136;
	
	  ;% rtB.ksmj2ks1ry
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 137;
	
	  ;% rtB.jt50mttmmc
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 138;
	
	  ;% rtB.i3k3ladn4s
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 139;
	
	  ;% rtB.iusqw5vol4
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 140;
	
	  ;% rtB.ioirosbkbv
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 141;
	
	  ;% rtB.bkz5gblmt2
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 143;
	
	  ;% rtB.jbv4oeizoh
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 343;
	
	  ;% rtB.jnz2ccaipm
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 345;
	
	  ;% rtB.ewsxkq0wzp
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 347;
	
	  ;% rtB.la0fvqhabk
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 547;
	
	  ;% rtB.cazq3bcp4v
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 549;
	
	  ;% rtB.el0hi2mpax
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 749;
	
	  ;% rtB.pviaul0ind
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 750;
	
	  ;% rtB.dvxrwfxmke
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 751;
	
	  ;% rtB.k2r1v43eue
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 752;
	
	  ;% rtB.ms400ves34
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 952;
	
	  ;% rtB.bkld5544on
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 953;
	
	  ;% rtB.hvk4gr05kp
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 954;
	
	  ;% rtB.kyq4ddwnt5
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 955;
	
	  ;% rtB.katlkd05we
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 956;
	
	  ;% rtB.e312d3rw1k
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 957;
	
	  ;% rtB.okmcolqmmp
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 958;
	
	  ;% rtB.d3wmvrdgp5
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 959;
	
	  ;% rtB.orga5rxyo4
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 960;
	
	  ;% rtB.faenhustsh
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 961;
	
	  ;% rtB.c1ucoxgukl
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 962;
	
	  ;% rtB.nnkwaky0vo
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 963;
	
	  ;% rtB.grqskhisxe
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 964;
	
	  ;% rtB.nwi2u1x5jv
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 965;
	
	  ;% rtB.pgv3a43g3a
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 966;
	
	  ;% rtB.bywih0a2yp
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 967;
	
	  ;% rtB.gok32izhkr
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 968;
	
	  ;% rtB.pkaciejeq4
	  section.data(103).logicalSrcIdx = 102;
	  section.data(103).dtTransOffset = 969;
	
	  ;% rtB.ahbxhfing1
	  section.data(104).logicalSrcIdx = 103;
	  section.data(104).dtTransOffset = 970;
	
	  ;% rtB.nkt1wwkpxk
	  section.data(105).logicalSrcIdx = 104;
	  section.data(105).dtTransOffset = 971;
	
	  ;% rtB.pr32bh5ab0
	  section.data(106).logicalSrcIdx = 105;
	  section.data(106).dtTransOffset = 972;
	
	  ;% rtB.gebkbee1ff
	  section.data(107).logicalSrcIdx = 106;
	  section.data(107).dtTransOffset = 973;
	
	  ;% rtB.oashgqc3jo
	  section.data(108).logicalSrcIdx = 107;
	  section.data(108).dtTransOffset = 974;
	
	  ;% rtB.mbhd03n5qp
	  section.data(109).logicalSrcIdx = 108;
	  section.data(109).dtTransOffset = 975;
	
	  ;% rtB.ld2pf1geuj
	  section.data(110).logicalSrcIdx = 109;
	  section.data(110).dtTransOffset = 976;
	
	  ;% rtB.ngwlyiii4t
	  section.data(111).logicalSrcIdx = 110;
	  section.data(111).dtTransOffset = 977;
	
	  ;% rtB.mmhpsmc2xu
	  section.data(112).logicalSrcIdx = 111;
	  section.data(112).dtTransOffset = 978;
	
	  ;% rtB.foapkh0xzh
	  section.data(113).logicalSrcIdx = 112;
	  section.data(113).dtTransOffset = 979;
	
	  ;% rtB.fwwgncxyps
	  section.data(114).logicalSrcIdx = 113;
	  section.data(114).dtTransOffset = 980;
	
	  ;% rtB.eol02jxukg
	  section.data(115).logicalSrcIdx = 114;
	  section.data(115).dtTransOffset = 981;
	
	  ;% rtB.hqdf5p5g5k
	  section.data(116).logicalSrcIdx = 115;
	  section.data(116).dtTransOffset = 982;
	
	  ;% rtB.ordb0vcov4
	  section.data(117).logicalSrcIdx = 116;
	  section.data(117).dtTransOffset = 983;
	
	  ;% rtB.ec0lm5oxpo
	  section.data(118).logicalSrcIdx = 117;
	  section.data(118).dtTransOffset = 984;
	
	  ;% rtB.jbkeye4siv
	  section.data(119).logicalSrcIdx = 118;
	  section.data(119).dtTransOffset = 985;
	
	  ;% rtB.aj3gcmhe30
	  section.data(120).logicalSrcIdx = 119;
	  section.data(120).dtTransOffset = 986;
	
	  ;% rtB.pakxhumxso
	  section.data(121).logicalSrcIdx = 120;
	  section.data(121).dtTransOffset = 987;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtB.jlxfvkiytb.p4suqxiggq
	  section.data(1).logicalSrcIdx = 121;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.jlxfvkiytb.g1q3oofyrj
	  section.data(2).logicalSrcIdx = 122;
	  section.data(2).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtB.mpnopdrqui.p4suqxiggq
	  section.data(1).logicalSrcIdx = 123;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.mpnopdrqui.g1q3oofyrj
	  section.data(2).logicalSrcIdx = 124;
	  section.data(2).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.csjm5qcu5l.j4xgvi25fi
	  section.data(1).logicalSrcIdx = 125;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% rtB.csjm5qcu5l.f0ix3jjnpf
	  section.data(1).logicalSrcIdx = 126;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.csjm5qcu5l.m0fwlvevxl
	  section.data(2).logicalSrcIdx = 127;
	  section.data(2).dtTransOffset = 200;
	
	  ;% rtB.csjm5qcu5l.ntofjobsep
	  section.data(3).logicalSrcIdx = 128;
	  section.data(3).dtTransOffset = 40200;
	
	  ;% rtB.csjm5qcu5l.bvdahqrkgv
	  section.data(4).logicalSrcIdx = 129;
	  section.data(4).dtTransOffset = 40400;
	
	  ;% rtB.csjm5qcu5l.fyq3rr4pxa
	  section.data(5).logicalSrcIdx = 130;
	  section.data(5).dtTransOffset = 40600;
	
	  ;% rtB.csjm5qcu5l.deyysf5gta
	  section.data(6).logicalSrcIdx = 131;
	  section.data(6).dtTransOffset = 40800;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.hk2fxt1axd.j4xgvi25fi
	  section.data(1).logicalSrcIdx = 132;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% rtB.hk2fxt1axd.f0ix3jjnpf
	  section.data(1).logicalSrcIdx = 133;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.hk2fxt1axd.m0fwlvevxl
	  section.data(2).logicalSrcIdx = 134;
	  section.data(2).dtTransOffset = 200;
	
	  ;% rtB.hk2fxt1axd.ntofjobsep
	  section.data(3).logicalSrcIdx = 135;
	  section.data(3).dtTransOffset = 40200;
	
	  ;% rtB.hk2fxt1axd.bvdahqrkgv
	  section.data(4).logicalSrcIdx = 136;
	  section.data(4).dtTransOffset = 40400;
	
	  ;% rtB.hk2fxt1axd.fyq3rr4pxa
	  section.data(5).logicalSrcIdx = 137;
	  section.data(5).dtTransOffset = 40600;
	
	  ;% rtB.hk2fxt1axd.deyysf5gta
	  section.data(6).logicalSrcIdx = 138;
	  section.data(6).dtTransOffset = 40800;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.pncwbu0dto.e3galh2ets
	  section.data(1).logicalSrcIdx = 139;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.n4wqmwk0ih.e3galh2ets
	  section.data(1).logicalSrcIdx = 140;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.d5gh3z0nbz.e3galh2ets
	  section.data(1).logicalSrcIdx = 141;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(10) = section;
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
    nTotSects     = 5;
    sectIdxOffset = 10;
    
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
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% rtDW.hunjvlw225
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.awjkgmzkcd
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.hdyfm4w10o
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.or3xy3rhzp
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.bmgxo1oskk
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.jojdexj25k
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.a0h21jsgxr
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.i0isqogxyp
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.lpcfsl5mnp
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.msyicwvkh0
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 208;
	
	  ;% rtDW.fkh51dxhfd
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 210;
	
	  ;% rtDW.gye4sfowa3
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 410;
	
	  ;% rtDW.lr5gxlhuv0
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 412;
	
	  ;% rtDW.fncmzwylce
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 413;
	
	  ;% rtDW.kecva0uppz
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 414;
	
	  ;% rtDW.h5y1kpt3c4
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 415;
	
	  ;% rtDW.jl0qdrh0vh
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 416;
	
	  ;% rtDW.mnsutipu10
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 417;
	
	  ;% rtDW.l5wlqfkerm
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 418;
	
	  ;% rtDW.nonseywoew
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 419;
	
	  ;% rtDW.hshq4edjvp
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 420;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 18;
      section.data(18)  = dumData; %prealloc
      
	  ;% rtDW.czgjtdfwfq
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.gidtjgtmom.LoggedData
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 22;
	
	  ;% rtDW.jccz1ddyws.LoggedData
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 24;
	
	  ;% rtDW.dclcvurcmy.LoggedData
	  section.data(4).logicalSrcIdx = 24;
	  section.data(4).dtTransOffset = 26;
	
	  ;% rtDW.nxjrrg4ysr.LoggedData
	  section.data(5).logicalSrcIdx = 25;
	  section.data(5).dtTransOffset = 28;
	
	  ;% rtDW.ocecg4ocie.LoggedData
	  section.data(6).logicalSrcIdx = 26;
	  section.data(6).dtTransOffset = 29;
	
	  ;% rtDW.lspsi4qeub.LoggedData
	  section.data(7).logicalSrcIdx = 27;
	  section.data(7).dtTransOffset = 30;
	
	  ;% rtDW.mgssy21dt0.LoggedData
	  section.data(8).logicalSrcIdx = 28;
	  section.data(8).dtTransOffset = 31;
	
	  ;% rtDW.kh5noeu1rm.LoggedData
	  section.data(9).logicalSrcIdx = 29;
	  section.data(9).dtTransOffset = 32;
	
	  ;% rtDW.cgn3m4t1dq.LoggedData
	  section.data(10).logicalSrcIdx = 30;
	  section.data(10).dtTransOffset = 33;
	
	  ;% rtDW.bqpn4jk0dr.LoggedData
	  section.data(11).logicalSrcIdx = 31;
	  section.data(11).dtTransOffset = 34;
	
	  ;% rtDW.hjgbl1mg0e
	  section.data(12).logicalSrcIdx = 32;
	  section.data(12).dtTransOffset = 36;
	
	  ;% rtDW.ft0tza0nlt
	  section.data(13).logicalSrcIdx = 33;
	  section.data(13).dtTransOffset = 44;
	
	  ;% rtDW.ds4l2typev.LoggedData
	  section.data(14).logicalSrcIdx = 34;
	  section.data(14).dtTransOffset = 52;
	
	  ;% rtDW.glvudhqxv5.LoggedData
	  section.data(15).logicalSrcIdx = 35;
	  section.data(15).dtTransOffset = 54;
	
	  ;% rtDW.ma225rjwd5.LoggedData
	  section.data(16).logicalSrcIdx = 36;
	  section.data(16).dtTransOffset = 55;
	
	  ;% rtDW.fisxfl23bd.LoggedData
	  section.data(17).logicalSrcIdx = 37;
	  section.data(17).dtTransOffset = 57;
	
	  ;% rtDW.n3t2d1e0mr.LoggedData
	  section.data(18).logicalSrcIdx = 38;
	  section.data(18).dtTransOffset = 59;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% rtDW.bbj41wyypv
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ji0mtgeizs
	  section.data(2).logicalSrcIdx = 40;
	  section.data(2).dtTransOffset = 23;
	
	  ;% rtDW.ohg4iyas0q
	  section.data(3).logicalSrcIdx = 41;
	  section.data(3).dtTransOffset = 51;
	
	  ;% rtDW.peojzkhro0
	  section.data(4).logicalSrcIdx = 42;
	  section.data(4).dtTransOffset = 52;
	
	  ;% rtDW.adqiufmg2m
	  section.data(5).logicalSrcIdx = 43;
	  section.data(5).dtTransOffset = 53;
	
	  ;% rtDW.k4n10av0pz
	  section.data(6).logicalSrcIdx = 44;
	  section.data(6).dtTransOffset = 54;
	
	  ;% rtDW.l1tbjsdipx
	  section.data(7).logicalSrcIdx = 45;
	  section.data(7).dtTransOffset = 55;
	
	  ;% rtDW.kam4r3pt4e
	  section.data(8).logicalSrcIdx = 46;
	  section.data(8).dtTransOffset = 56;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.jlxfvkiytb.mgzovusthk
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.jlxfvkiytb.n1jqioztuc
	  section.data(2).logicalSrcIdx = 48;
	  section.data(2).dtTransOffset = 200;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.mpnopdrqui.mgzovusthk
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.mpnopdrqui.n1jqioztuc
	  section.data(2).logicalSrcIdx = 50;
	  section.data(2).dtTransOffset = 200;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
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


  targMap.checksum0 = 771051142;
  targMap.checksum1 = 3907438473;
  targMap.checksum2 = 2959251210;
  targMap.checksum3 = 1793715238;

