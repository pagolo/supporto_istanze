<?php
/**
 * hook for the Views module
 */
/**
 * Implements hook_views_data().
 */ 
function supporto_istanze_views_data() {
  $data = array();
  $data['supporto_istanze']['table']['group'] = 'Supporto istanze';
  $data['supporto_istanze']['table']['join'] = array(
    'webform_submissions' => array(
      'left_field' => 'sid',
      'field' => 'submission_id',
    ),
  );
  $data['supporto_istanze']['tid'] = array(
    'title' => 'Chiave di istanza',
    'help' => 'Indice primario tabella supporto_istanze.',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
  );
  $data['supporto_istanze']['submission_id'] = array(
    'title' => 'Chiave di submission',
    'help' => 'Indice primario tabella webform_submissions.',
    'relationship' => array(
      'base' => 'webform_submissions', // The name of the table to join with.
      'base field' => 'sid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => 'Relazione supporto_istanze',
      'title' => 'Relazione con la tabella delle Submissions',
      'help' =>'Collega le tabelle webform_submissions e supporto_istanze',
    ),
  );
  $data['supporto_istanze']['protocollo_stato'] = array(
    'title' => 'Protocollo',
    'help' => 'Istanza protocollata.',
    'field' => array(
      'handler' => 'supporto_istanze_protocollo_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
/*
  $data['supporto_istanze']['acquisito_stato'] = array(
    'title' => 'Acquisito',
    'help' => 'Istanza acquisita.',
    'field' => array(
      'handler' => 'supporto_istanze_acquisito_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
*/
  $data['supporto_istanze']['concedibile_stato'] = array(
    'title' => 'Verifica ufficio',
    'help' => 'Istanza concedibile.',
    'field' => array(
      'handler' => 'supporto_istanze_concedibile_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['visto_stato'] = array(
    'title' => 'Visto del DS',
    'help' => 'Istanza accolta.',
    'field' => array(
      'handler' => 'supporto_istanze_visto_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['evaso_data'] = array(
    'title' => 'Evaso',
    'help' => 'Istanza evasa il...',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['motivazioni'] = array(
    'title' => 'Motivazioni',
    'help' => 'Le motivazioni per il rifiuto della istanza.',
    'field' => array(
      'handler' => 'supporto_istanze_motivazioni_views_handler_field',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function supporto_istanze_views_handlers() {
  return array(
  'info' => array(
    'path' => drupal_get_path('module', 'supporto_istanze'),
    ),
  'handlers' => array(
    'supporto_istanze_protocollo_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),
/*        
    'supporto_istanze_acquisito_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),
*/        
    'supporto_istanze_concedibile_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_visto_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_motivazioni_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    ),
  );
}
