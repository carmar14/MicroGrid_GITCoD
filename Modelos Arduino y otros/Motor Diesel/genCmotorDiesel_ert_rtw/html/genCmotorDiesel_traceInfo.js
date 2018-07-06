function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Actuador */
	this.urlHashMap["genCmotorDiesel:36"] = "genCmotorDiesel.c:66&genCmotorDiesel.h:78";
	/* <Root>/Par de Carga */
	this.urlHashMap["genCmotorDiesel:37"] = "genCmotorDiesel.c:51&genCmotorDiesel.h:79";
	/* <Root>/ Generador1 */
	this.urlHashMap["genCmotorDiesel:25"] = "genCmotorDiesel.c:59";
	/* <Root>/Actuador - Motor Tm=0.01s */
	this.urlHashMap["genCmotorDiesel:27"] = "genCmotorDiesel.c:42,77,78&genCmotorDiesel.h:69";
	/* <Root>/Delay Tm=0.01 */
	this.urlHashMap["genCmotorDiesel:28"] = "genCmotorDiesel.c:43,65,75&genCmotorDiesel.h:68";
	/* <Root>/Eje Tm=0.01s */
	this.urlHashMap["genCmotorDiesel:29"] = "genCmotorDiesel.c:50,82,83&genCmotorDiesel.h:70";
	/* <Root>/Scope3 */
	this.urlHashMap["genCmotorDiesel:32"] = "genCmotorDiesel.h:73";
	/* <Root>/Sum2 */
	this.urlHashMap["genCmotorDiesel:33"] = "genCmotorDiesel.c:52";
	/* <Root>/Out1 */
	this.urlHashMap["genCmotorDiesel:38"] = "genCmotorDiesel.c:62&genCmotorDiesel.h:84";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "genCmotorDiesel"};
	this.sidHashMap["genCmotorDiesel"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Actuador"] = {sid: "genCmotorDiesel:36"};
	this.sidHashMap["genCmotorDiesel:36"] = {rtwname: "<Root>/Actuador"};
	this.rtwnameHashMap["<Root>/Par de Carga"] = {sid: "genCmotorDiesel:37"};
	this.sidHashMap["genCmotorDiesel:37"] = {rtwname: "<Root>/Par de Carga"};
	this.rtwnameHashMap["<Root>/ Generador1"] = {sid: "genCmotorDiesel:25"};
	this.sidHashMap["genCmotorDiesel:25"] = {rtwname: "<Root>/ Generador1"};
	this.rtwnameHashMap["<Root>/Actuador - Motor Tm=0.01s"] = {sid: "genCmotorDiesel:27"};
	this.sidHashMap["genCmotorDiesel:27"] = {rtwname: "<Root>/Actuador - Motor Tm=0.01s"};
	this.rtwnameHashMap["<Root>/Build ERT"] = {sid: "genCmotorDiesel:3"};
	this.sidHashMap["genCmotorDiesel:3"] = {rtwname: "<Root>/Build ERT"};
	this.rtwnameHashMap["<Root>/Delay Tm=0.01"] = {sid: "genCmotorDiesel:28"};
	this.sidHashMap["genCmotorDiesel:28"] = {rtwname: "<Root>/Delay Tm=0.01"};
	this.rtwnameHashMap["<Root>/Eje Tm=0.01s"] = {sid: "genCmotorDiesel:29"};
	this.sidHashMap["genCmotorDiesel:29"] = {rtwname: "<Root>/Eje Tm=0.01s"};
	this.rtwnameHashMap["<Root>/Mux2"] = {sid: "genCmotorDiesel:30"};
	this.sidHashMap["genCmotorDiesel:30"] = {rtwname: "<Root>/Mux2"};
	this.rtwnameHashMap["<Root>/Scope3"] = {sid: "genCmotorDiesel:32"};
	this.sidHashMap["genCmotorDiesel:32"] = {rtwname: "<Root>/Scope3"};
	this.rtwnameHashMap["<Root>/Sum2"] = {sid: "genCmotorDiesel:33"};
	this.sidHashMap["genCmotorDiesel:33"] = {rtwname: "<Root>/Sum2"};
	this.rtwnameHashMap["<Root>/View Code Generation Templates"] = {sid: "genCmotorDiesel:20"};
	this.sidHashMap["genCmotorDiesel:20"] = {rtwname: "<Root>/View Code Generation Templates"};
	this.rtwnameHashMap["<Root>/Out1"] = {sid: "genCmotorDiesel:38"};
	this.sidHashMap["genCmotorDiesel:38"] = {rtwname: "<Root>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
