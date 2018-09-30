<?php

/**
 * @file
 * Definition of supporto_istanze_evaso_data_views_handler_filter.
 */

/**
 * Filter handler for evaso_data.
 *
 * @ingroup views_filter_handlers
 */
class supporto_istanze_evaso_data_views_handler_filter extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('Evaso');
    $this->accept_null = TRUE;
  }
  function get_value_options() {
    $this->value_options = array(1 => t('Evaso'), 0 => t('Non evaso'));
  }
}
