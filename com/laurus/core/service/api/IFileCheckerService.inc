<?php
import("com.laurus.core.services.IService");
import('com.laurus.core.file.IFile');
import('com.laurus.core.file.ImageFile');
interface IFileCheckerService extends IService{
   const NAME="FILECHECKER_SERVICE";
   const AllowedExtensions="allowedExtensions";
   public function checkExtenstion(\ImageFile $image);
   public function getAllowedExtensionFor($key);
}

?>
