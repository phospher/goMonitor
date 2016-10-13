FROM openjdk:8

ARG SPARK_PATH

COPY $SPARK_PATH /spark

COPY docker-entrypoint.sh /
RUN chmod a+x /docker-entrypoint.sh

ENTRYPOINT ["/docker-entrypoint.sh"]