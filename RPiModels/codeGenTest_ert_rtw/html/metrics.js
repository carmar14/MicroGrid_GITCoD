function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDW"] = {file: "C:\\Users\\erich\\Documents\\Matlab2017a\\MicroGrid_GITCoD\\RPiModels\\codeGenTest_ert_rtw\\codeGenTest.c",
	size: 8};
	 this.metricsArray.var["rtU"] = {file: "C:\\Users\\erich\\Documents\\Matlab2017a\\MicroGrid_GITCoD\\RPiModels\\codeGenTest_ert_rtw\\codeGenTest.c",
	size: 8};
	 this.metricsArray.var["rtY"] = {file: "C:\\Users\\erich\\Documents\\Matlab2017a\\MicroGrid_GITCoD\\RPiModels\\codeGenTest_ert_rtw\\codeGenTest.c",
	size: 8};
	 this.metricsArray.fcn["codeGenTest_initialize"] = {file: "C:\\Users\\erich\\Documents\\Matlab2017a\\MicroGrid_GITCoD\\RPiModels\\codeGenTest_ert_rtw\\codeGenTest.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["codeGenTest_step"] = {file: "C:\\Users\\erich\\Documents\\Matlab2017a\\MicroGrid_GITCoD\\RPiModels\\codeGenTest_ert_rtw\\codeGenTest.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="codeGenTest_metrics.html">Global Memory: 24(bytes) Maximum Stack: 0(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
