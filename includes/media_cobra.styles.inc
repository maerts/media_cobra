<?php

/**
 * @file media_cobra/includes/media_cobra.styles.inc
 * Styles definitions for Media: Cobra.
 */

/**
 * Implementation of Styles module hook_styles_register().
 */
function media_cobra_styles_register() {
  return array(
    'MediaCobraStyles' => array(
      'field_types' => 'file',
      'name' => t('MediaCobra'),
      'description' => t('Media Cobra styles.'),
      'path' => drupal_get_path('module', 'media_cobra') .'/includes',
      'file' => 'media_cobra.styles.inc',
    ),
  );
}

/**
 *  Implements hook_styles_containers(). (Deprecated in version 2)
 */
function media_cobra_styles_containers() {
  return array(
    'file' => array(
      'containers' => array(
        'media_cobra' => array(
          'label' => t('Cobra Styles'),
          'data' => array(
            'streams' => array(
              'cobra',
            ),
            'mimetypes' => array(
              'video/cobra',
            ),
          ),
          'weight' => 0,
          'filter callback' => 'media_cobra_formatter_filter',
          'themes' => array(
            'field_formatter_styles' => 'media_cobra_field_formatter_styles',
            'styles' => 'media_cobra_styles',
            'preview' => 'media_cobra_preview_style',
          ),
          'description' => t('Cobra Styles will display embedded Cobra videos and thumbnails to your choosing, such as by resizing, setting colors, and autoplay. You can !manage.', array('!manage' => l(t('manage your Cobra styles here'), 'admin/config/media/media-cobra-styles'))),
        ),
      ),
    ),
  );
}

function media_cobra_formatter_filter($variables) {
  if (isset($variables['object'])) {
    $object = $variables['object'];
    return (file_uri_scheme($object->uri) == 'cobra') && ($object->filemime == 'video/cobra');
  }
}

/**
 * Implementation of the File Styles module's hook_file_styles_filter().
 */
function media_cobra_file_styles_filter($object) {
  if ((file_uri_scheme($object->uri) == 'cobra') && ($object->filemime == 'video/cobra')) {
    return 'media_cobra';
  }
}

/**
 *  Implements hook_styles_styles().
 */
function media_cobra_styles_styles() {
  $styles = array(
    'file' => array(
      'containers' => array(
        'media_cobra' => array(
          'styles' => array(
            'cobra_thumbnail' => array(
              'name' => 'cobra_thumbnail',
              'effects' => array(
                array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 100, 'height' => 75)),
              ),
            ),
            'cobra_preview' => array(
              'name' => 'cobra_preview',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 1)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 220, 'height' => 165)),
              ),
            ),
            'cobra_full' => array(
              'name' => 'cobra_full',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 0)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 640, 'height' => 480)),
                array('label' => t('Full screen'), 'name' => 'fullscreen', 'data' => array('fullscreen' => 1)),
              ),
            ),
          ),
        ),
      ),
    ),
  );

  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $styles['file']['containers']['media_cobra']['styles']['cobra_thumbnail_' . $style_name] = array(
      'name' => 'cobra_thumbnail_' . $style_name,
      'image_style' => $style_name,
      'effects' => array(
        array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
      ),
    );
  }

  return $styles;
}

/**
 *  Implements hook_styles_presets().
 */
function media_cobra_styles_presets() {
  $presets = array(
    'file' => array(
      'square_thumbnail' => array(
        'media_cobra' => array(
          'cobra_thumbnail_square_thumbnail',
        ),
      ),
      'thumbnail' => array(
        'media_cobra' => array(
          'cobra_thumbnail',
        ),
      ),
      'small' => array(
        'media_cobra' => array(
          'cobra_preview',
        ),
      ),
      'large' => array(
        'media_cobra' => array(
          'cobra_full',
        ),
      ),
      'original' => array(
        'media_cobra' => array(
          'cobra_full',
        ),
      ),
    ),
  );
  return $presets;
}

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_cobra_styles_default_containers() {
  // We append YouTube to the file containers.
  return array(
    'file' => array(
      'containers' => array(
        'media_cobra' => array(
          'class' => 'MediaCobraStyles',
          'name' => 'media_cobra',
          'label' => t('Cobra'),
          'preview' => 'media_cobra_preview_style',
        ),
      ),
    ),
  );
}


/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_cobra_styles_default_presets() {
  $presets = array(
    'file' => array(
      'containers' => array(
        'media_cobra' => array(
          'default preset' => 'unlinked_thumbnail',
          'styles' => array(
            'original' => array(
              'default preset' => 'video',
            ),
            'thumbnail' => array(
              'default preset' => 'linked_thumbnail',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'medium' => array(
              'default preset' => 'linked_medium',
            ),
            'large' => array(
              'default preset' => 'large_video',
            ),
          ),
          'presets' => array(
            'video' => array(
              array(
                'name' => 'video',
                'settings' => array(),
              ),
            ),
            'large_video' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 640,
                  'height' => 390,
                ),
              ),
              array(
                'name' => 'video',
                'settings' => array(),
              ),
            ),
          ),
        ),
      ),
    ),
  );
  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $presets['file']['containers']['media_cobra']['presets']['linked_' . $style_name] = array(
      array(
        'name' => 'linkToMedia',
        'settings' => array(),
      ),
      array(
        'name' => 'imageStyle',
        'settings' => array(
          'image_style' => $style_name,
        ),
      ),
      array(
        'name' => 'thumbnail',
        'settings' => array(),
      ),
    );
    $presets['file']['containers']['media_cobra']['presets']['unlinked_' . $style_name] = $presets['file']['containers']['media_cobra']['presets']['linked_' . $style_name];
    array_shift($presets['file']['containers']['media_cobra']['presets']['unlinked_' . $style_name]);
  }
  return $presets;
}
