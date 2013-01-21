<?php

/**
 *  @file
 *  Create a Cobra Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $cobra = new ResourceYouTubeStreamWrapper('cobra://[video-code]');
 */
class MediaCobraStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://www.cobra.be/permalink/';

  function getTarget($f) {
    return FALSE;
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/cobra';
  }

  function getOriginalThumbnailPath() {
    $parts = $this->get_parameters();
    return 'http://www.cobra.be/polopoly_fs/1.643665!image/1985559922.gif';
  }

  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = 'public://media-cobra/' . check_plain($parts['v']) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      @copy($this->getOriginalThumbnailPath(), $local_path);
    }
    return $local_path;
  }
}
