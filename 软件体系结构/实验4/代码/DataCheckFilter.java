package org.example;

public class DataCheckFilter extends Filter {
	public void handleRequest(DataRequest dataRequest){
		System.out.println("数据校验过滤器");
		if (this.successor != null) {
			this.successor.handleRequest(dataRequest);
		}
	}
}
