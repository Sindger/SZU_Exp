package org.example;

public class JPGImage extends Image{
    public JPGImage(Filter filter) {
        super(filter);
        // TODO Auto-generated constructor stub
    }
    @Override
    public void operation() {
        // TODO Auto-generated method stub
        filter.addFilter();
    }
}
