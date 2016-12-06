<?php

import('com.laurus.core.file.IFileTypes');
/**
 * This Interface defines All the FileTypes Requeired.
 * If want to add new File Type Just add another File name and assign  int value to it.
 * @author Kunal Mestri
 *   
 */
interface IFile{
   /**
    * @return IFileTypes::FileType
    */
    public  function getFileType();
    /**
    * @return String
    */
    public function  getFileName();
    public function  setFileName($p);
}

?>
