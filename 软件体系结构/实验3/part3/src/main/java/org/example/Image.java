package org.example;

public abstract class Image {
    protected Filter filter;
    public Image(Filter filter) {
        super();
        this.filter = filter;
    }
    public abstract void operation();
}
