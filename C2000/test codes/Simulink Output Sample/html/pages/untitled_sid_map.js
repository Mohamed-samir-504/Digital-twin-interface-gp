function RTW_SidParentMap() {
    this.sidParentMap = new Array();
    this.sidParentMap["untitled:14"] = "untitled";
    this.sidParentMap["untitled:15"] = "untitled";
    this.getParentSid = function(sid) { return this.sidParentMap[sid];}
}
    RTW_SidParentMap.instance = new RTW_SidParentMap();
