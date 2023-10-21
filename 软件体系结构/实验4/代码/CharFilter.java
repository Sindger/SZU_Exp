package org.example;

public class CharFilter extends Filter {
	public void handleRequest(DataRequest dataRequest){
		System.out.println("字符编码过滤器");
		if (this.successor != null) {
			this.successor.handleRequest(dataRequest);
		}
	}
}
