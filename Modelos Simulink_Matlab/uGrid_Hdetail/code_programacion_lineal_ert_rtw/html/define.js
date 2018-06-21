function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:33,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:70,type:"fcn"};
this.def["code_programacion_lineal_B"] = {file: "code_programacion_lineal_c.html",line:20,type:"var"};
this.def["code_programacion_lineal_DW"] = {file: "code_programacion_lineal_c.html",line:23,type:"var"};
this.def["code_programacion_lineal_U"] = {file: "code_programacion_lineal_c.html",line:26,type:"var"};
this.def["code_programacion_lineal_Y"] = {file: "code_programacion_lineal_c.html",line:29,type:"var"};
this.def["code_programacion_lineal_M_"] = {file: "code_programacion_lineal_c.html",line:32,type:"var"};
this.def["code_programacion_lineal_M"] = {file: "code_programacion_lineal_c.html",line:33,type:"var"};
this.def["LinProg_BuildMatrices_ActivePow"] = {file: "code_programacion_lineal_c.html",line:41,type:"fcn"};
this.def["code_programacion_lineal_step"] = {file: "code_programacion_lineal_c.html",line:153,type:"fcn"};
this.def["code_programacion_lineal_initialize"] = {file: "code_programacion_lineal_c.html",line:231,type:"fcn"};
this.def["code_programacion_lineal_terminate"] = {file: "code_programacion_lineal_c.html",line:920,type:"fcn"};
this.def["B_code_programacion_lineal_T"] = {file: "code_programacion_lineal_h.html",line:107,type:"type"};
this.def["DW_code_programacion_lineal_T"] = {file: "code_programacion_lineal_h.html",line:113,type:"type"};
this.def["ExtU_code_programacion_lineal_T"] = {file: "code_programacion_lineal_h.html",line:129,type:"type"};
this.def["ExtY_code_programacion_lineal_T"] = {file: "code_programacion_lineal_h.html",line:137,type:"type"};
this.def["RT_MODEL_code_programacion_lineal_T"] = {file: "code_programacion_lineal_types_h.html",line:21,type:"type"};
this.def["rtGetInf"] = {file: "rtGetInf_c.html",line:27,type:"fcn"};
this.def["rtGetInfF"] = {file: "rtGetInf_c.html",line:51,type:"fcn"};
this.def["rtGetMinusInf"] = {file: "rtGetInf_c.html",line:62,type:"fcn"};
this.def["rtGetMinusInfF"] = {file: "rtGetInf_c.html",line:86,type:"fcn"};
this.def["rtGetNaN"] = {file: "rtGetNaN_c.html",line:27,type:"fcn"};
this.def["rtGetNaNF"] = {file: "rtGetNaN_c.html",line:51,type:"fcn"};
this.def["rtInf"] = {file: "rt_nonfinite_c.html",line:25,type:"var"};
this.def["rtMinusInf"] = {file: "rt_nonfinite_c.html",line:26,type:"var"};
this.def["rtNaN"] = {file: "rt_nonfinite_c.html",line:27,type:"var"};
this.def["rtInfF"] = {file: "rt_nonfinite_c.html",line:28,type:"var"};
this.def["rtMinusInfF"] = {file: "rt_nonfinite_c.html",line:29,type:"var"};
this.def["rtNaNF"] = {file: "rt_nonfinite_c.html",line:30,type:"var"};
this.def["rt_InitInfAndNaN"] = {file: "rt_nonfinite_c.html",line:36,type:"fcn"};
this.def["rtIsInf"] = {file: "rt_nonfinite_c.html",line:48,type:"fcn"};
this.def["rtIsInfF"] = {file: "rt_nonfinite_c.html",line:54,type:"fcn"};
this.def["rtIsNaN"] = {file: "rt_nonfinite_c.html",line:60,type:"fcn"};
this.def["rtIsNaNF"] = {file: "rt_nonfinite_c.html",line:66,type:"fcn"};
this.def["BigEndianIEEEDouble"] = {file: "rt_nonfinite_h.html",line:37,type:"type"};
this.def["LittleEndianIEEEDouble"] = {file: "rt_nonfinite_h.html",line:44,type:"type"};
this.def["IEEESingle"] = {file: "rt_nonfinite_h.html",line:51,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:23,type:"type"};
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
	this.html2SrcPath["code_programacion_lineal_c.html"] = "../code_programacion_lineal.c";
	this.html2Root["code_programacion_lineal_c.html"] = "code_programacion_lineal_c.html";
	this.html2SrcPath["code_programacion_lineal_h.html"] = "../code_programacion_lineal.h";
	this.html2Root["code_programacion_lineal_h.html"] = "code_programacion_lineal_h.html";
	this.html2SrcPath["code_programacion_lineal_private_h.html"] = "../code_programacion_lineal_private.h";
	this.html2Root["code_programacion_lineal_private_h.html"] = "code_programacion_lineal_private_h.html";
	this.html2SrcPath["code_programacion_lineal_types_h.html"] = "../code_programacion_lineal_types.h";
	this.html2Root["code_programacion_lineal_types_h.html"] = "code_programacion_lineal_types_h.html";
	this.html2SrcPath["rtGetInf_c.html"] = "../rtGetInf.c";
	this.html2Root["rtGetInf_c.html"] = "rtGetInf_c.html";
	this.html2SrcPath["rtGetInf_h.html"] = "../rtGetInf.h";
	this.html2Root["rtGetInf_h.html"] = "rtGetInf_h.html";
	this.html2SrcPath["rtGetNaN_c.html"] = "../rtGetNaN.c";
	this.html2Root["rtGetNaN_c.html"] = "rtGetNaN_c.html";
	this.html2SrcPath["rtGetNaN_h.html"] = "../rtGetNaN.h";
	this.html2Root["rtGetNaN_h.html"] = "rtGetNaN_h.html";
	this.html2SrcPath["rt_nonfinite_c.html"] = "../rt_nonfinite.c";
	this.html2Root["rt_nonfinite_c.html"] = "rt_nonfinite_c.html";
	this.html2SrcPath["rt_nonfinite_h.html"] = "../rt_nonfinite.h";
	this.html2Root["rt_nonfinite_h.html"] = "rt_nonfinite_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["qp_linprog_c.html"] = "qp_linprog.c";
	this.html2Root["qp_linprog_c.html"] = "qp_linprog_c.html";
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
"ert_main_c.html","code_programacion_lineal_c.html","code_programacion_lineal_h.html","code_programacion_lineal_private_h.html","code_programacion_lineal_types_h.html","rtGetInf_c.html","rtGetInf_h.html","rtGetNaN_c.html","rtGetNaN_h.html","rt_nonfinite_c.html","rt_nonfinite_h.html","rtwtypes_h.html","qp_linprog_c.html"];
