package org.example;

public abstract class DataClassifyTemplate {
	public abstract void callAlgorithm();
	public void convertData(){
		System.out.println("转换数据格式");
	}
	public void display(){
		System.out.println("展示结果");
	}
	public void process(){
		this.readData();
		this.convertData();
		this.callAlgorithm();
		this.display();
	}
	public void readData(){
		System.out.println("读数据");
	}
}
