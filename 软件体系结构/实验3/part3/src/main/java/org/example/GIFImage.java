package org.example;

public class GIFImage extends Image{
    public GIFImage(Filter filter) {
        super(filter);
        // TODO Auto-generated constructor stub
    }
    @Override
    public void operation() {
        // TODO Auto-generated method stub
        filter.addFilter();
    }
}
