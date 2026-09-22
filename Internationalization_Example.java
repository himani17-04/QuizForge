package javaservletpackage;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import  jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@WebServlet ("/Internationalization_Example")
public class Internationalization_Example extends HttpServlet
{
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        String Title = "Detecting Locale";
        Locale locale = request.getLocale();
        String language = locale.getLanguage();
        String country = locale.getCountry();
        String Doctype = "<!Doctype Detecting Locale>";
        out.println(Doctype+"<html><head><title>"+Title+"</title></head>"+
                "<body bgcolor = 'lime'+" +
                ">"+"<h1 align = 'center'>"+Title+"</h1>\n"+
                "<h2>LANGUAGE : "+language+"</h2>"+
                "<h2>COUNTRY : "+country+"</h2>"+
                "<h2>LOCALE : "+locale+"</h2>"+
                "</body></html>");
    }
}
