FROM openjdk:8

COPY spark-2.0.0-bin-hadoop2.7.tgz /
RUN tar -xf /spark-2.0.0-bin-hadoop2.7.tgz -C /
RUN mv /spark-2.0.0-bin-hadoop2.7 /spark

COPY docker-entrypoint.sh /
RUN chmod a+x /docker-entrypoint.sh

ENTRYPOINT ["/docker-entrypoint.sh"]