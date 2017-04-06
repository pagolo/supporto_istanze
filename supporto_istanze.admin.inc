<?php
/**
 * @file
 * settings file
 */
 
/**
 * Settings form.
 */
function supporto_istanze_admin_settings_form() {
  $my_nodes = array();
  node_types_rebuild();
  $node_types = node_type_get_types();
  foreach ($node_types as $node_type) {
    $my_nodes[$node_type->type] = $node_type->type;
  }

  $form['supporto_istanze_content1'] = array(
    '#type' => 'fieldset',
    '#title' => 'Tipi di contenuto',
  );
  $form['supporto_istanze_content1']['supporto_istanze_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => 'tipi di contenuto usati per le istanze',
    '#default_value' => variable_get('supporto_istanze_node_types', array('istanze_del_personale' => 'istanze_del_personale')),
    '#options' => $my_nodes,
    '#multiple' => TRUE,
  );
  $form['supporto_istanze_content2'] = array(
    '#type' => 'fieldset',
    '#title' => 'Email della segreteria',
  );
  $form['supporto_istanze_content2']['supporto_istanze_email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#maxlength' => 254,
    '#description' => 'indirizzo e-mail valido',
    '#required' => TRUE,
    '#default_value' => variable_get('supporto_istanze_email', ''),
  );
  $form['supporto_istanze_content2']['supporto_istanze_notification_email'] = array(
    '#type' => 'checkbox',
    '#title' => 'Invia, in modo predefinito, email di istanza evasa alla segreteria',
    '#defaul_value' => variable_get('supporto_istanze_notification_email', FALSE),
    '#attributes' => variable_get('supporto_istanze_notification_email', FALSE) ? array('checked' => 'checked') : NULL,
  );
  $form['supporto_istanze_content3'] = array(
    '#type' => 'fieldset',
    '#title' => 'Testo delle email di notifica',
  );
  $form['supporto_istanze_content3']['supporto_istanze_notification_body'] = array(
    '#type' => 'textarea',
    '#title' => "Notifica all'utente. E' possibile modificare il testo del messaggio utilizzando i riferimenti preceduti da @ come da esempio.",
    '#default_value' => variable_get('supporto_istanze_notification_body', "La sua istanza @istanza, n. @istanza_id del @data, è stata @esito."),
  );
  $form['supporto_istanze_content3']['supporto_istanze_segreteria_body'] = array(
    '#type' => 'textarea',
    '#title' => "Email alla segreteria. E' possibile modificare il testo del messaggio utilizzando i riferimenti come sopra.",
    '#default_value' => variable_get('supporto_istanze_segreteria_body', "L'istanza @istanza, n. @istanza_id del @data presentata da @nome, è stata @esito."),
  );
  $form['supporto_istanze_content3']['supporto_istanze_notification_footer'] = array(
    '#type' => 'textarea',
    '#title' => "Saluti e firma. E' possibile modificare il testo del messaggio utilizzando i riferimenti come sopra.",
    '#default_value' => variable_get('supporto_istanze_notification_footer', "Cordiali saluti,\n@operatore (@qualifica_operatore)."),
  );
  $form['supporto_istanze_content4'] = array(
    '#type' => 'fieldset',
    '#title' => 'File di segnatura allegato email',
  );
  $form['supporto_istanze_content4']['supporto_istanze_instance_signature'] = array(
    '#type' => 'checkbox',
    '#title' => 'Segnatura su trasmissione istanza',
    '#defaul_value' => variable_get('supporto_istanze_instance_signature', FALSE),
    '#attributes' => variable_get('supporto_istanze_instance_signature', FALSE) ? array('checked' => 'checked') : NULL,
  );
  $form['supporto_istanze_content4']['supporto_istanze_evaded_signature'] = array(
    '#type' => 'checkbox',
    '#title' => 'Segnatura su istanza evasa',
    '#defaul_value' => variable_get('supporto_istanze_evaded_signature', FALSE),
    '#attributes' => variable_get('supporto_istanze_evaded_signature', FALSE) ? array('checked' => 'checked') : NULL,
  );
  $form['supporto_istanze_content4']['supporto_istanze_nome_scuola'] = array(
    '#type' => 'textfield',
    '#title' => 'Denominazione ufficiale dell\'Istituto',
    '#default_value' => variable_get('supporto_istanze_nome_scuola', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_codice_amm'] = array(
    '#type' => 'textfield',
    '#title' => 'Codice amministrazione',
    '#default_value' => variable_get('supporto_istanze_codice_amm', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_codice_aoo'] = array(
    '#type' => 'textfield',
    '#title' => 'Codice AOO',
    '#default_value' => variable_get('supporto_istanze_codice_aoo', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_toponimo'] = array(
    '#type' => 'textfield',
    '#title' => 'Toponimo (via o piazza etc.)',
    '#default_value' => variable_get('supporto_istanze_toponimo', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_civico'] = array(
    '#type' => 'textfield',
    '#title' => 'Numero civico',
    '#default_value' => variable_get('supporto_istanze_civico', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_cap'] = array(
    '#type' => 'textfield',
    '#title' => 'CAP',
    '#default_value' => variable_get('supporto_istanze_cap', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_comune'] = array(
    '#type' => 'textfield',
    '#title' => 'Comune',
    '#default_value' => variable_get('supporto_istanze_comune', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_provincia'] = array(
    '#type' => 'textfield',
    '#title' => 'Provincia (SIGLA)',
    '#maxlength' => 2,
    '#default_value' => variable_get('supporto_istanze_provincia', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_fax'] = array(
    '#type' => 'textfield',
    '#title' => 'Fax',
    '#default_value' => variable_get('supporto_istanze_fax', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_telefono'] = array(
    '#type' => 'textfield',
    '#title' => 'Telefono',
    '#default_value' => variable_get('supporto_istanze_telefono', ''),
  );

  $form['#submit'][] = '_supporto_istanze_reset_fields';
  return system_settings_form($form);
}