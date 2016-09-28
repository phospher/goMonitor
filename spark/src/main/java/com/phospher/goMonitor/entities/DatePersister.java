package com.phospher.goMonitor.entities;

import java.sql.SQLException;
import java.util.Date;

import com.j256.ormlite.field.FieldType;
import com.j256.ormlite.field.SqlType;
import com.j256.ormlite.misc.SqlExceptionUtil;
import com.j256.ormlite.support.DatabaseResults;
import com.j256.ormlite.field.types.*;

public class DatePersister extends BaseDateType {

	private static final DatePersister singleTon = new DatePersister();

	public static DatePersister getSingleton() {
		return singleTon;
	}

	private DatePersister() {
		super(SqlType.LONG);
	}

	protected DatePersister(SqlType sqlType, Class<?>[] classes) {
		super(sqlType, classes);
	}

	@Override
	public Object parseDefaultString(FieldType fieldType, String defaultStr) throws SQLException {
		try {
			return Long.parseLong(defaultStr);
		} catch (NumberFormatException e) {
			throw SqlExceptionUtil.create("Problems with field " + fieldType + " parsing default date-long value: "
					+ defaultStr, e);
		}
	}

	@Override
	public Object resultToSqlArg(FieldType fieldType, DatabaseResults results, int columnPos) throws SQLException {
		return results.getLong(columnPos);
	}

	@Override
	public Object sqlArgToJava(FieldType fieldType, Object sqlArg, int columnPos) {
		return new Date(((Long) sqlArg) * 1000);
	}

	@Override
	public Object javaToSqlArg(FieldType fieldType, Object obj) {
		Date date = (Date) obj;
		return (Long) date.getTime() / 1000;
	}

	@Override
	public boolean isEscapedValue() {
		return false;
	}

	@Override
	public Class<?> getPrimaryClass() {
		return Date.class;
	}
}