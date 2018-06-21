function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/A */
	this.urlHashMap["example_SQProblem:20"] = "example_SQProblem.c:33,425,446&example_SQProblem.h:99&example_SQProblem_data.c:22";
	/* <Root>/H */
	this.urlHashMap["example_SQProblem:18"] = "example_SQProblem.c:34,426,447&example_SQProblem.h:104&example_SQProblem_data.c:27";
	/* <Root>/Scope */
	this.urlHashMap["example_SQProblem:17"] = "msg=rtwMsg_reducedBlock&block=example_SQProblem:17";
	/* <Root>/f */
	this.urlHashMap["example_SQProblem:19"] = "example_SQProblem.c:35,427,448&example_SQProblem.h:109&example_SQProblem_data.c:32";
	/* <Root>/lb */
	this.urlHashMap["example_SQProblem:21"] = "example_SQProblem.c:36,428,449&example_SQProblem.h:114&example_SQProblem_data.c:37";
	/* <Root>/lbA */
	this.urlHashMap["example_SQProblem:23"] = "example_SQProblem.c:37,429,450&example_SQProblem.h:119&example_SQProblem_data.c:42";
	/* <Root>/qpOASES */
	this.urlHashMap["example_SQProblem:9"] = "example_SQProblem.c:32,42,424,433,445,454&example_SQProblem.h:85,86,87,88,93";
	/* <Root>/ub */
	this.urlHashMap["example_SQProblem:22"] = "example_SQProblem.c:38,430,451&example_SQProblem.h:124&example_SQProblem_data.c:47";
	/* <Root>/ubA */
	this.urlHashMap["example_SQProblem:24"] = "example_SQProblem.c:39,431,452&example_SQProblem.h:129&example_SQProblem_data.c:52";
	/* <Root>/x,
fval,
exitflag,
iter */
	this.urlHashMap["example_SQProblem:8"] = "msg=rtwMsg_reducedBlock&block=example_SQProblem:8";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "example_SQProblem"};
	this.sidHashMap["example_SQProblem"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/A"] = {sid: "example_SQProblem:20"};
	this.sidHashMap["example_SQProblem:20"] = {rtwname: "<Root>/A"};
	this.rtwnameHashMap["<Root>/H"] = {sid: "example_SQProblem:18"};
	this.sidHashMap["example_SQProblem:18"] = {rtwname: "<Root>/H"};
	this.rtwnameHashMap["<Root>/Scope"] = {sid: "example_SQProblem:17"};
	this.sidHashMap["example_SQProblem:17"] = {rtwname: "<Root>/Scope"};
	this.rtwnameHashMap["<Root>/f"] = {sid: "example_SQProblem:19"};
	this.sidHashMap["example_SQProblem:19"] = {rtwname: "<Root>/f"};
	this.rtwnameHashMap["<Root>/lb"] = {sid: "example_SQProblem:21"};
	this.sidHashMap["example_SQProblem:21"] = {rtwname: "<Root>/lb"};
	this.rtwnameHashMap["<Root>/lbA"] = {sid: "example_SQProblem:23"};
	this.sidHashMap["example_SQProblem:23"] = {rtwname: "<Root>/lbA"};
	this.rtwnameHashMap["<Root>/qpOASES"] = {sid: "example_SQProblem:9"};
	this.sidHashMap["example_SQProblem:9"] = {rtwname: "<Root>/qpOASES"};
	this.rtwnameHashMap["<Root>/ub"] = {sid: "example_SQProblem:22"};
	this.sidHashMap["example_SQProblem:22"] = {rtwname: "<Root>/ub"};
	this.rtwnameHashMap["<Root>/ubA"] = {sid: "example_SQProblem:24"};
	this.sidHashMap["example_SQProblem:24"] = {rtwname: "<Root>/ubA"};
	this.rtwnameHashMap["<Root>/x, fval, exitflag, iter"] = {sid: "example_SQProblem:8"};
	this.sidHashMap["example_SQProblem:8"] = {rtwname: "<Root>/x, fval, exitflag, iter"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
