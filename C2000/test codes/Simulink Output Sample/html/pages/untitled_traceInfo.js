function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/SCI Receive */
	this.urlHashMap["untitled:14"] = "untitled.c:28,29,30,31,32,33,34,35,36,39,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,62,65,66,67,70,71,72,73,74,75,76,77,79,80,81,82,83,84,85,86,87,90,91,92,93,94,135,138,139,140&untitled.h:45";
	/* <Root>/SCI Transmit */
	this.urlHashMap["untitled:15"] = "untitled.c:96,97,98,99,100,101,102,105,106,107,108,110,113,114,115,116,118,119,120";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "untitled"};
	this.sidHashMap["untitled"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/SCI Receive"] = {sid: "untitled:14"};
	this.sidHashMap["untitled:14"] = {rtwname: "<Root>/SCI Receive"};
	this.rtwnameHashMap["<Root>/SCI Transmit"] = {sid: "untitled:15"};
	this.sidHashMap["untitled:15"] = {rtwname: "<Root>/SCI Transmit"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
