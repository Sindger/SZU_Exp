import org.jdom2.JDOMException;
import org.jdom2.input.SAXBuilder;
import org.jdom2.output.XMLOutputter;
import org.jdom2.Document;
import org.jdom2.Element;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
public class JdomParsing {
    public JdomParsing(){
        String XmlPath="books.xml";
        SAXBuilder builder=new SAXBuilder(false);
        try {
            Document doc=builder.build(XmlPath);
            Element books=doc.getRootElement();
            Element AddBook = new Element("book");
            AddBook.addContent(new Element("BookID").setText("5"));
            AddBook.addContent(new Element("Name").setText("Harry Potter"));
            AddBook.addContent(new Element("Price").setText("40.0"));
            books.addContent(AddBook);
            List<Element> booklist=books.getChildren("book");
            for (Iterator iter = booklist.iterator(); iter.hasNext();) {
                Element book = (Element) iter.next();
                if ("Pride and Prejudice".equals(book.getChildTextTrim("Name"))) {
                    book.getChild("Price").setText("56.7");
                }
                String email=book.getChildTextTrim("BookID");
                System.out.println(email);
                String Name=book.getChildTextTrim("Name");
                System.out.println(Name);
                String Price=book.getChildTextTrim("Price");
                System.out.println(Price);
            }
            XMLOutputter outputter=new XMLOutputter();
            outputter.output(doc,new FileOutputStream(XmlPath));
        } catch (JDOMException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        new JdomParsing();
    }
}