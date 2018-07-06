function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Actuador */
	this.urlHashMap["Motor_Diesel_paC:54"] = "Motor_Diesel_paC.c:42&Motor_Diesel_paC.h:45";
	/* <Root>/Par */
	this.urlHashMap["Motor_Diesel_paC:56"] = "Motor_Diesel_paC.c:54&Motor_Diesel_paC.h:46";
	/* <Root>/ 1 */
	this.urlHashMap["Motor_Diesel_paC:52"] = "Motor_Diesel_paC.c:75";
	/* <Root>/ Generador1 */
	this.urlHashMap["Motor_Diesel_paC:34"] = "Motor_Diesel_paC.c:67";
	/* <Root>/Actuador - Motor Tm=0.01s */
	this.urlHashMap["Motor_Diesel_paC:45"] = "Motor_Diesel_paC.c:41,71&Motor_Diesel_paC.h:38";
	/* <Root>/Delay Tm=0.01 */
	this.urlHashMap["Motor_Diesel_paC:47"] = "Motor_Diesel_paC.c:53,74,84&Motor_Diesel_paC.h:39";
	/* <Root>/Eje Tm=0.01s */
	this.urlHashMap["Motor_Diesel_paC:46"] = "Motor_Diesel_paC.c:52,86&Motor_Diesel_paC.h:40";
	/* <Root>/Sum2 */
	this.urlHashMap["Motor_Diesel_paC:42"] = "Motor_Diesel_paC.c:55";
	/* <Root>/Flujo */
	this.urlHashMap["Motor_Diesel_paC:57"] = "Motor_Diesel_paC.c:49&Motor_Diesel_paC.h:51";
	/* <Root>/Velocidad */
	this.urlHashMap["Motor_Diesel_paC:58"] = "Motor_Diesel_paC.c:63&Motor_Diesel_paC.h:52";
	/* <Root>/Tensión */
	this.urlHashMap["Motor_Diesel_paC:59"] = "Motor_Diesel_paC.c:66&Motor_Diesel_paC.h:53";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "Motor_Diesel_paC"};
	this.sidHashMap["Motor_Diesel_paC"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Actuador"] = {sid: "Motor_Diesel_paC:54"};
	this.sidHashMap["Motor_Diesel_paC:54"] = {rtwname: "<Root>/Actuador"};
	this.rtwnameHashMap["<Root>/Par"] = {sid: "Motor_Diesel_paC:56"};
	this.sidHashMap["Motor_Diesel_paC:56"] = {rtwname: "<Root>/Par"};
	this.rtwnameHashMap["<Root>/ 1"] = {sid: "Motor_Diesel_paC:52"};
	this.sidHashMap["Motor_Diesel_paC:52"] = {rtwname: "<Root>/ 1"};
	this.rtwnameHashMap["<Root>/ Generador1"] = {sid: "Motor_Diesel_paC:34"};
	this.sidHashMap["Motor_Diesel_paC:34"] = {rtwname: "<Root>/ Generador1"};
	this.rtwnameHashMap["<Root>/Actuador - Motor Tm=0.01s"] = {sid: "Motor_Diesel_paC:45"};
	this.sidHashMap["Motor_Diesel_paC:45"] = {rtwname: "<Root>/Actuador - Motor Tm=0.01s"};
	this.rtwnameHashMap["<Root>/Delay Tm=0.01"] = {sid: "Motor_Diesel_paC:47"};
	this.sidHashMap["Motor_Diesel_paC:47"] = {rtwname: "<Root>/Delay Tm=0.01"};
	this.rtwnameHashMap["<Root>/Eje Tm=0.01s"] = {sid: "Motor_Diesel_paC:46"};
	this.sidHashMap["Motor_Diesel_paC:46"] = {rtwname: "<Root>/Eje Tm=0.01s"};
	this.rtwnameHashMap["<Root>/Sum2"] = {sid: "Motor_Diesel_paC:42"};
	this.sidHashMap["Motor_Diesel_paC:42"] = {rtwname: "<Root>/Sum2"};
	this.rtwnameHashMap["<Root>/Flujo"] = {sid: "Motor_Diesel_paC:57"};
	this.sidHashMap["Motor_Diesel_paC:57"] = {rtwname: "<Root>/Flujo"};
	this.rtwnameHashMap["<Root>/Velocidad"] = {sid: "Motor_Diesel_paC:58"};
	this.sidHashMap["Motor_Diesel_paC:58"] = {rtwname: "<Root>/Velocidad"};
	this.rtwnameHashMap["<Root>/Tensión"] = {sid: "Motor_Diesel_paC:59"};
	this.sidHashMap["Motor_Diesel_paC:59"] = {rtwname: "<Root>/Tensión"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
