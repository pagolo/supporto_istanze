<?php

/**
 * @file
 * Definition of supporto_istanze_elaborato_data_views_handler_filter.
 */

/**
 * Filter handler for elaborato_data.
 *
 * @ingroup views_filter_handlers
 */
class supporto_istanze_elaborato_data_views_handler_filter extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('Elaborato');
    $this->accept_null = TRUE;
  }
  function get_value_options() {
    $this->value_options = array(1 => t('Elaborato'), 0 => t('Non elaborato'));
  }
}
