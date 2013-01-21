<?php

/**
 * @file media_cobra/includes/media_cobra.variables.inc
 * Variable defaults for Media: YouTube.
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('MEDIA_COBRA_NAMESPACE', 'media_cobra__');

/**
 * Wrapper for variable_get() using the Media: YouTube variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending MEDIA_COBRA_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the media_cobra_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see media_cobra_variable_set()
 * @see media_cobra_variable_del()
 * @see media_cobra_variable_default()
 */
function media_cobra_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing is still
  // desired.
  if (!isset($default)) {
    $default = media_cobra_variable_default($name);
  }
  // Namespace all variables.
  $variable_name = MEDIA_COBRA_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the Media: YouTube variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending MEDIA_COBRA_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see media_cobra_variable_get()
 * @see media_cobra_variable_del()
 * @see media_cobra_variable_default()
 */
function media_cobra_variable_set($name, $value) {
  $variable_name = MEDIA_COBRA_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the Media: YouTube variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending MEDIA_COBRA_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see media_cobra_variable_get()
 * @see media_cobra_variable_set()
 * @see media_cobra_variable_default()
 */
function media_cobra_variable_del($name) {
  $variable_name = MEDIA_COBRA_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: Cobra namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the MEDIA_COBRA_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see media_cobra_variable_get()
 * @see media_cobra_variable_set()
 * @see media_cobra_variable_del()
 */
function media_cobra_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'width' => 560,
      'height' =>340,
      'autoplay' => FALSE,
      'fullscreen' => TRUE,
      'preview_uri' => 'cobra://v/-jubiv7QUco',
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  MEDIA_COBRA_NAMESPACE.
 */
function media_cobra_variable_name($name) {
  return MEDIA_COBRA_NAMESPACE . $name;
}
