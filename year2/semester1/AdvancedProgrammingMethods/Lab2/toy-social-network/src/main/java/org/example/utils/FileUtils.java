package org.example.utils;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

/**
 * Class for managing functions related to reading/writing from files
 */
public class FileUtils {

    /**
     * Copies the content from templateFileName into targetFileName
     * Used primarily for testing
     * @param targetFileName the name of the target file
     * @param templateFileName the name of the template file
     */
    public static void copyTargetTemplate(String targetFileName, String templateFileName) {
        String cleanTemplatePath = templateFileName.startsWith("/") ? templateFileName.substring(1) : templateFileName;
        try (InputStream inputStream = FileUtils.class.getClassLoader().getResourceAsStream(cleanTemplatePath)) {
            if (inputStream == null) {
                throw new IllegalStateException("Cannot find template file: " + cleanTemplatePath);
            }

            Files.copy(inputStream, Paths.get(targetFileName), StandardCopyOption.REPLACE_EXISTING);
        }

        catch (Exception e) {
            throw new RuntimeException(e.getMessage());
        }
    }
}