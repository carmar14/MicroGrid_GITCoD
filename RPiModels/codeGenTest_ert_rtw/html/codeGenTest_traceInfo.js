function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/entrada */
	this.urlHashMap["codeGenTest:1"] = "codeGenTest.c:33,41&codeGenTest.h:34";
	/* <Root>/Scope */
	this.urlHashMap["codeGenTest:10"] = "msg=rtwMsg_notTraceable&block=codeGenTest:10";
	/* <Root>/Step */
	this.urlHashMap["codeGenTest:11"] = "msg=rtwMsg_notTraceable&block=codeGenTest:11";
	/* <Root>/salida */
	this.urlHashMap["codeGenTest:6"] = "codeGenTest.c:34,42&codeGenTest.h:39";
	/* <S1>/Discrete
State Space */
	this.urlHashMap["codeGenTest:9:4"] = "codeGenTest.c:32,40&codeGenTest.h:29";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "codeGenTest"};
	this.sidHashMap["codeGenTest"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "codeGenTest:9"};
	this.sidHashMap["codeGenTest:9"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<Root>/entrada"] = {sid: "codeGenTest:1"};
	this.sidHashMap["codeGenTest:1"] = {rtwname: "<Root>/entrada"};
	this.rtwnameHashMap["<Root>/Discrete Transfer Fcn (with initial outputs)"] = {sid: "codeGenTest:9"};
	this.sidHashMap["codeGenTest:9"] = {rtwname: "<Root>/Discrete Transfer Fcn (with initial outputs)"};
	this.rtwnameHashMap["<Root>/Scope"] = {sid: "codeGenTest:10"};
	this.sidHashMap["codeGenTest:10"] = {rtwname: "<Root>/Scope"};
	this.rtwnameHashMap["<Root>/Step"] = {sid: "codeGenTest:11"};
	this.sidHashMap["codeGenTest:11"] = {rtwname: "<Root>/Step"};
	this.rtwnameHashMap["<Root>/salida"] = {sid: "codeGenTest:6"};
	this.sidHashMap["codeGenTest:6"] = {rtwname: "<Root>/salida"};
	this.rtwnameHashMap["<S1>/In1"] = {sid: "codeGenTest:9:3"};
	this.sidHashMap["codeGenTest:9:3"] = {rtwname: "<S1>/In1"};
	this.rtwnameHashMap["<S1>/Discrete State Space"] = {sid: "codeGenTest:9:4"};
	this.sidHashMap["codeGenTest:9:4"] = {rtwname: "<S1>/Discrete State Space"};
	this.rtwnameHashMap["<S1>/Out1"] = {sid: "codeGenTest:9:5"};
	this.sidHashMap["codeGenTest:9:5"] = {rtwname: "<S1>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
