package org.example;

public class BMPImage extends Image{
    public BMPImage(Filter filter) {
        super(filter);
        // TODO Auto-generated constructor stub
    }
    @Override
    public void operation() {
        // TODO Auto-generated method stub
        filter.addFilter();
    }
}
