package org.example;

public abstract class Filter {
    protected Filter successor;
    public void setSuccessor(Filter successor) {
        this.successor = successor;
    }
    public abstract void handleRequest(DataRequest dataRequest);
}
