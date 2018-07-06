function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:33,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:119,type:"fcn"};
this.def["rtB"] = {file: "rtwdemo_examplemain_c.html",line:20,type:"var"};
this.def["rtDWork"] = {file: "rtwdemo_examplemain_c.html",line:23,type:"var"};
this.def["rtU"] = {file: "rtwdemo_examplemain_c.html",line:26,type:"var"};
this.def["rtY"] = {file: "rtwdemo_examplemain_c.html",line:29,type:"var"};
this.def["rtM_"] = {file: "rtwdemo_examplemain_c.html",line:32,type:"var"};
this.def["rtM"] = {file: "rtwdemo_examplemain_c.html",line:33,type:"var"};
this.def["rtwdemo_examplemain_step0"] = {file: "rtwdemo_examplemain_c.html",line:36,type:"fcn"};
this.def["rtwdemo_examplemain_step1"] = {file: "rtwdemo_examplemain_c.html",line:75,type:"fcn"};
this.def["rtwdemo_examplemain_initialize"] = {file: "rtwdemo_examplemain_c.html",line:87,type:"fcn"};
this.def["BlockIO"] = {file: "rtwdemo_examplemain_h.html",line:37,type:"type"};
this.def["D_Work"] = {file: "rtwdemo_examplemain_h.html",line:43,type:"type"};
this.def["ExternalInputs"] = {file: "rtwdemo_examplemain_h.html",line:49,type:"type"};
this.def["ExternalOutputs"] = {file: "rtwdemo_examplemain_h.html",line:55,type:"type"};
this.def["RT_MODEL"] = {file: "rtwdemo_examplemain_types_h.html",line:20,type:"type"};
this.def["int8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:42,type:"type"};
this.def["uint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:43,type:"type"};
this.def["int16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:44,type:"type"};
this.def["uint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:45,type:"type"};
this.def["int32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:46,type:"type"};
this.def["uint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:47,type:"type"};
this.def["real32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:48,type:"type"};
this.def["real64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:49,type:"type"};
this.def["real_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:55,type:"type"};
this.def["time_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:56,type:"type"};
this.def["boolean_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:57,type:"type"};
this.def["int_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:58,type:"type"};
this.def["uint_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:59,type:"type"};
this.def["ulong_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:60,type:"type"};
this.def["char_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:61,type:"type"};
this.def["uchar_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:62,type:"type"};
this.def["byte_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:63,type:"type"};
this.def["creal32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:73,type:"type"};
this.def["creal64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:78,type:"type"};
this.def["creal_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:83,type:"type"};
this.def["cint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:90,type:"type"};
this.def["cuint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:97,type:"type"};
this.def["cint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:104,type:"type"};
this.def["cuint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:111,type:"type"};
this.def["cint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:118,type:"type"};
this.def["cuint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:125,type:"type"};
this.def["pointer_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:143,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["rtwdemo_examplemain_c.html"] = "../rtwdemo_examplemain.c";
	this.html2Root["rtwdemo_examplemain_c.html"] = "rtwdemo_examplemain_c.html";
	this.html2SrcPath["rtwdemo_examplemain_h.html"] = "../rtwdemo_examplemain.h";
	this.html2Root["rtwdemo_examplemain_h.html"] = "rtwdemo_examplemain_h.html";
	this.html2SrcPath["rtwdemo_examplemain_private_h.html"] = "../rtwdemo_examplemain_private.h";
	this.html2Root["rtwdemo_examplemain_private_h.html"] = "rtwdemo_examplemain_private_h.html";
	this.html2SrcPath["rtwdemo_examplemain_types_h.html"] = "../rtwdemo_examplemain_types.h";
	this.html2Root["rtwdemo_examplemain_types_h.html"] = "rtwdemo_examplemain_types_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "../../slprj/ert/_sharedutils/html/rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","rtwdemo_examplemain_c.html","rtwdemo_examplemain_h.html","rtwdemo_examplemain_private_h.html","rtwdemo_examplemain_types_h.html","rtwtypes_h.html"];
