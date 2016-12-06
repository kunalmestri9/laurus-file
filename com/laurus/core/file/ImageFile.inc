<?php
import('com.laurus.core.file.IFile');
class  ImageFile implements IFile{
    private /*String*/ $path;
   
    public function  __construct($path) {
        if(is_string($path)){
            $this->path=$path;
        }
        else
          throw new Exception("Parameter must be type of String");
    }

    public function getThumnailImage(){
        
    }

    public function getFileName() {
        return $this->path;
    }
    public function getFileType() {
        return IFileTypes::IMAGE;
    }

    public function setFileName($path) {
          $this->path = $path;
    }
}




?>
