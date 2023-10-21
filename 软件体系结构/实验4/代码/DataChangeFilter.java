package org.example;

public class DataChangeFilter extends Filter {
	public void handleRequest(DataRequest dataRequest){
		System.out.println("数据转换过滤器");
		if (this.successor != null) {
			this.successor.handleRequest(dataRequest);
		}
	}

}
