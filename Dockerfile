FROM httpd:2.4
COPY foo.conf /etc/httpd/conf.d/
COPY mod_foo.so /usr/lib/apache2/modules/
